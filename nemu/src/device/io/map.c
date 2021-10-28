//此文件用于完成真机内存和虚拟内存的映射与读写.
//更准确的说,此文件直接与真机交互.实际上映射并没有在此完成.
#include <isa.h>
#include <memory/host.h>
#include <memory/vaddr.h>
#include <device/map.h>

#define IO_SPACE_MAX (2 * 1024 * 1024)

static uint8_t *io_space = NULL;
static uint8_t *p_space = NULL;


uint8_t* new_space(int size) ;
//被每个设备初始化的时候调用,从已经申请的总 真机空间依次分配给各个设备.返回真机地址
static void check_bound(IOMap *map, paddr_t addr) ;//边界检查
static void invoke_callback(io_callback_t c, paddr_t offset, int len, bool is_write);//回调函数更新
void init_map() ;//初始化整个设备内存空间,并且赋值给p_space起始地址.此地址是物理地址,不是nemu中的虚拟地址
word_t map_read(paddr_t addr, int len, IOMap *map) ;//利用映射,表面上修改nemu虚拟字段,实际上是修改了映射到的真机内存
void map_write(paddr_t addr, int len, word_t data, IOMap *map) ;



uint8_t* new_space(int size) 
{
  uint8_t *p = p_space;
  // page aligned;
  size = (size + (PAGE_SIZE - 1)) & ~PAGE_MASK;
  p_space += size;//给每个设备分配空间,起始地址p,然后将整体空间的p_space移动到未使用的最初地址.此地址是物理地址,不是nemu中的虚拟地址
  assert(p_space - io_space < IO_SPACE_MAX);
   // printf("0x%p  p_space  0x%p   size 0x%08x\n ",p,p_space, size);//验证假设成立
  return p;
}


static void check_bound(IOMap *map, paddr_t addr) 
{
  if (map == NULL) 
  {
    Assert(map != NULL, "address (" FMT_PADDR ") is out of bound at pc = " FMT_WORD, addr, cpu.pc);
  } 
  else 
  {
    Assert(addr <= map->high && addr >= map->low,
        "address (" FMT_PADDR ") is out of bound {%s} [" FMT_PADDR ", " FMT_PADDR "] at pc = " FMT_WORD,
        addr, map->name, map->low, map->high, cpu.pc);
  }
}


static void invoke_callback(io_callback_t c, paddr_t offset, int len, bool is_write) 
{
  if (c != NULL) { c(offset, len, is_write); }//映射读写完成后,对于设备相应的回调函数进行更新.
}




void init_map() 
{
  io_space = malloc(IO_SPACE_MAX);
  assert(io_space);
  p_space = io_space;//初始化整个设备内存空间,并且赋值给p_space起始地址.此地址是物理地址,不是nemu中的虚拟地址
}

/*
其中map_read()和map_write()用于将地址addr映射到map所指示的目标空间, 
并进行访问. 访问时, 可能会触发相应的回调函数, 对设备和目标空间的状态进
行更新. 由于NEMU是单线程程序, 因此只能串行模拟整个计算机系统的工作, 每
次进行I/O读写的时候, 才会调用设备提供的回调函数(callback). 
*/


word_t map_read(paddr_t addr, int len, IOMap *map) 
{
  assert(len >= 1 && len <= 8);
  check_bound(map, addr);
  paddr_t offset = addr - map->low;
  invoke_callback(map->callback, offset, len, false); // prepare data to read
  word_t ret = host_read(map->space + offset, len);
  return ret;
}


void map_write(paddr_t addr, int len, word_t data, IOMap *map) 
{
  assert(len >= 1 && len <= 8);
  check_bound(map, addr);
  paddr_t offset = addr - map->low;
  host_write(map->space + offset, len, data);
  invoke_callback(map->callback, offset, len, true);
}//假模假样,看似是读写到nemu的内存,实际上私下里干了偷天换日的龌龊事,对IOMAP中储存的真机内存进行了读写.
