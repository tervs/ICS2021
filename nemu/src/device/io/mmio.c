//此文件完成内存映射.属于是中介,或者叫做翻译
//具体与真机的交互由map.c完成
#include <device/map.h>

#define NR_MAP 16

static IOMap maps[NR_MAP] = {};//定义映射列表
static int nr_map = 0;

static IOMap* fetch_mmio_map(paddr_t addr) 
{
  int mapid = find_mapid_by_addr(maps, nr_map, addr);//函数是字面意思
  return (mapid == -1 ? NULL : &maps[mapid]);//返回指向结构体的指针.
}
//根据虚拟地址,返回对应字段的设备(的结构体指针)


/* device interface */
void add_mmio_map(const char *name, paddr_t addr, void *space, uint32_t len, io_callback_t callback) 
{
  assert(nr_map < NR_MAP);
  maps[nr_map] = (IOMap){ .name = name, .low = addr, .high = addr + len - 1, .space = space, .callback = callback };
  Log("Add mmio map '%s' at [" FMT_PADDR ", " FMT_PADDR "]", maps[nr_map].name, maps[nr_map].low, maps[nr_map].high);
  nr_map ++;
}
//将物理地址映射到指定的nemu字段(虚拟字段),并且将已经初始化的设备加入maps数组,给定一个编号.
//IOMAPS 结构的maps记录了每个设备映射的具体情况,space指向到了真机空间.

/*

typedef struct {
  const char *name;
  // we treat ioaddr_t as paddr_t here
  paddr_t low;
  paddr_t high;
  void *space;//这里的space指定到了真机地址.工具人而已hhhh
  io_callback_t callback;
} IOMap;

*/



/* bus interface */
word_t mmio_read(paddr_t addr, int len)
{
  return map_read(addr, len, fetch_mmio_map(addr));
}

void mmio_write(paddr_t addr, int len, word_t data) 
{
  map_write(addr, len, data, fetch_mmio_map(addr));
}
//ybb
//实际上调用了map函数.