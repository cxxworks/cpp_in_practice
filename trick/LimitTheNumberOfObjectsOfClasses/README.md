## 限制类对象的数量的方法

### 方法1
通过可计数的基类来限制派生类的实例的数量。

#### 流程
1. 实现一个计数用的基类Counted: a. 其构造函数累加计数，且当超过最大数量时抛出异常 b. 析构函数对递减计数
2. 派生类private继承Counted，并将自己的constructors声明为private，对外提供一个static的伪constructors

private继承是为了隐藏计数的细节，因为跟计数相关的细节是不用对外暴露的。

#### 缺点
1. 各种派生类继承同一个Counted, 共享同一个用于计数的静态全局变量（Counted::numObjects）
2. 带有private constructors的classes不能用来当作base classes, 也不能被嵌入于其它对象内。因此各派生类无法再作为base classes

### 方法2
基于方法1的问题，可将计数用的base class改为一个base class template，各派生类继承后可独享模板实例化后自身类的对象计数