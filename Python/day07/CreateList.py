import sys

def main():
    f = [x for x in range(1, 100)]
    print(f)

    f = [x + y for x in 'ABCDE' for y in '1234567']
    print(f)

    # 列表的生成表达式语法创建列表容器
    # 用这种语法创建列表之后元素已经准备就绪，所以需要耗费较多的内存空间
    f = [x ** 2 for x in range(1, 1000)]
    print(sys.getsizeof(f))

    # 注意下面的代码创建的不是一个列表而是一个生成器对象
    # 通过生成器可以获取到数据但它不占用额外的内存存储数据
    # 每次需要数据的时候就通过内部的运算得到数据（需要花费额外的时间）
    f = (x ** 2 for x in range(1, 1000))
    print(sys.getsizeof(f)) # 相比生成式生成器不占用存储数据的空间
    print(f)
    for val in f:
        # print(val)
        pass


    def fib(n):
        """
        斐波那契数列生成器
        :param n: 斐波那契数列
        :return: 生成器
        """
        a, b = 0, 1
        for _ in range(n):
            a, b = b, a + b
            yield a

    for val in fib(20):
        print(val)


if __name__ == '__main__':
    main()