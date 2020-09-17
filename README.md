# hanming
c语言实现高效汉明距离计算,并将其封装成python的扩展模块

```angular2
http://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetParallel

int hanming(uint64_t v1,  uint64_t  v2)
{
     uint64_t out = v1 ^ v2;
     out -= (out >> 1) & 0x5555555555555555;
     out = (0x3333333333333333 & out) + (0x3333333333333333 & (out >> 2));
     out = (out + (out >> 4)) & 0x0f0f0f0f0f0f0f0f;
     out &= 0x0f0f0f0f0f0f0f0f;
	 out *= 0x0101010101010101;
     return out >> 56;
}
```

安装方法
```angular2
python3 setup install
```

使用方法
```angular2
import hanming
distance = hanming.hanming_distance(8900000000,454646464)
```