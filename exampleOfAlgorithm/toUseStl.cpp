#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>//慢
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <iterator>
#include <algorithm>

using namespace std;
//除特别指明，以下所有字符串均为string类，下标从0起
/***************************************************s t r i n g*********************
定义时
a)      string s;    //生成一个空字符串s
b)      string s(str) //把str的值作为s的初值
c)      string s(str,stridx) //将字符串str内“始于位置stridx”的部分当作字符串的初值，下标从0起
d)      string s(str,stridx,len) //将字符串str内“始于stridx且长度为len(不超过str尾元素)”的部分作为字符串的初值
e)      string s(num,char) //生成一个字符串，包含num个char字符
*/
/*
字符串操作
a) =,assign()     //赋以新值
//		dest.assign("test"), dest.assign(str)
b) swap(str1,str2)     //交换字符串1,2的内容
c) +=,append(),push_back() //在尾部添加字符
d) insert() //插入字符
e) erase() //删除字符
f) clear() //删除全部字符
g) replace() //替换字符
h) + //串联字符串
i) ==,!=,<,<=,>,>=,compare()    //比较字符串
//			a.compare(s), (字典序)> < =返回1 -1 0
j) size(),length()    //返回字符串的字符数量
//        	s.size()
k) max_size() //返回能储存的最大字符个数
//			s.max_size()
l) empty()    //判断字符串是否为空
//			s.empty() 空1有0
m) [ ], at() //存取单一字符
//			a[0] 等价 s.at(0)
n) >>,getline() //从stream读取某值
//			cin>>s 遇空格回车停止, getline(cin, s)读入一行
o) c_str() //将内容以C_string返回
//        strcpy(cstr,s.c_str()); printf("%s", s.c_str());
p) data() //将内容以字符数组形 式返回
//        strcpy(chstr,s.data());
q) erase() // 删除字符
//		s.erase(1,3); 删除序号1-3的字符
r) insert() //插入字符
//		s.insert(0,"abc"),s.insert(0,s1) //在0位置后插入字符串
s)begin() end() //提供类似STL的迭代器支持
//		auto n = begin(s);
//		cout << *n << '\n';//输出s[0]
t) rbegin() rend() //逆向迭代器 rbegin是末元素
u) find() //查找
//      string s = "abcde";
        size_t pos = s.find('b',3), pos1 = s.find("bc");
        //pos == 1, pos1 == 2
*/
/**************************************************v e c t o r***********************
 * 不排序，按输入顺序排列
1) s[i]	直接以下标方式访问容器中的元素。
2) s.front()	返回首元素。
3) s.back()	返回尾元素。
4) s.push_back(x)	向表尾插入元素x。
5) s.size()		返回表长。
6) s.empty()	当表空时，返回真，否则返回假。
7) s.pop_back()		删除表尾元素。
8) s.begin()	返回指向首元素的随机存取迭代器。
9) s.end()		返回指向尾元素的下一个位置的随机存取迭代器。
10) s.insert(it, x)		向迭代器it 指向的元素前插入新元素val。
11) s.insert(it, n, x)		向迭代器it 指向的元素前插入n 个x。
12) s.insert(it, first, last)	将由迭代器first 和last 所指定的序列[first, last)插入到迭代器it指向的元素前面。
13) s.erase(it)	删除由迭代器it 所指向的元素。
14) s.erase(first, last)	删除由迭代器first 和last 所指定的序列[first, last)。
15) s.reserve(n)	预分配缓冲空间，使存储空间至少可容纳n 个元素。
16) s.resize(n) 改变序列的长度，超出的元素将会被删除，如果序列需要扩展（原空间小于n），元素默认值将填满扩展出的空间。
17) s.resize(n, val)	改变序列的长度，超出的元素将会被删除，如果序列需要扩展（原空间小于n），将用val 填满扩展出的空间。
18) s.clear()	删除容器中的所有的元素。
19) s.swap(v)	将s 与另一个vector 对象v 进行交换。
20) s.assign(first, last)	将序列替换成由迭代器first 和last 所指定的序列[first, last)。[first, last)不能是原序列中的一部分。
*/
/******************************************s e t 从小到大排列*******************
 * multiset的使用大致相同
1) s.insert(5);	插入
2) erase(iterator)	删除定位器iterator指向的值
3) erase(first,second)	删除定位器first和second之间的值
4) erase(key_value)	删除键值key_value的值，set中的删除操作是不进行任何的错误检查的，比如定位器的是否合法等等，所以用的时候自己一定要注意。
5) s.find(val);	查找，返回给定值的定位器，如果没找到则返回end()。
6) s.count(val)	返回的是被查找元素的个数，如果有，返回1；否则，返回0。因为一个键值在set只可能出现0或1次，这样就变成了判断某一键值是否在set出现过了。
7) s.begin()	返回set容器的第一个元素
8) s.end()	返回set容器的最后一个元素
9) s.clear()	删除set容器中的所有的元素
10) s.empty()	判断set容器是否为空
11) s.max_size()	返回set容器可能包含的元素最大个数
12) s.size()	返回当前set容器中的元素个数
13) s.rbegin()	返回末元素
14) s.rend()	返回的值和begin()相同
15) s.lower_bound(k)	指向第一个不大于k值的元素
	s.insert(2); s.insert(3); s.insert(4);
	auto lo = s.lower_bound(3) *lo==3
16) s.upper_bound(k)	指向第一个大于k值的元素
*/
/************************************************m a p****************
 * multimap 的使用大致相同，但没有重载[]运算符
 * 都根据key值升序排序
1) m.[key] = value;	插入或更新元素
2) insert(pair<,>(key,value))	插入元素
	map<string,int> m;
	m.insert(pair<string,int>("may",5));
3) m.size();	map元素个数
4) m.count(key)	返回的是被查找元素的个数。如果有，返回1；否则，返回0。注意，map中不存在相同元素，所以返回值只能是1或0。
		int n = m.count(key);
5) begin()	返回指向map头部的迭代器
6) clear(）	删除所有元素
7) empty()	如果map为空则返回true
8) end()	返回指向map末尾的迭代器
9) erase()	删除一个元素删除：erase(key) erase(it) //既可以按照key值删除，也可以按照迭代器删除
10) find()	查找一个元素
		map<string,int> m; m["july"] = 7;
		auto a = m.find("july");
		cout << a->second << '\n';
11) lower_bound(k)	返回键值k>=给定元素的第一个位置
12) rbegin()	返回一个指向map尾部的逆向迭代器, 末元素
13) rend()	返回一个指向map头部的逆向迭代器
14) swap()	交换两个map
15) upper_bound(k)	返回键值k>给定元素的第一个位置
*/
/************************s t a c k********
 * LIFO
1) empty() 堆栈为空则返回真
2) pop() 移除栈顶元素
3) push() 在栈顶增加元素
	s.push(val);
4) size() 返回栈中元素数目
5) top() 返回栈顶元素
*/
/**********q u e u e***********
 * FIFO
1) q.push(val) 入队，将 x 接到队列的末端。
2) q.pop() 出队，弹出队列的第一个元素，注意，并不会返回被弹出元素的值。
3) q.front()访问队首元素
4) q.back()访问队尾元素
5) q.empty()当队列空时，返回 true。
6) q.size() 访问队列中的元素个数\
*/
/**************p r i o r i  t y _ q u e u e*************
 * 定义,三个模板参数，第一个是元素类型，第二个容器类型，第三个是比较算子.
 * 其中后两个都可以省略，默认容器为 vector，默认算子为 less，即小的往前排，大的往后排（出队时序列尾的元素出队）
1) priority_queue<int> q1;
2) priority_queue< pair<int, int> > q2; // 注意在两个尖括号之间一定要留空格。
3) priority_queue<int, vector<int>, greater<int> > q3; // 定义小的先出队
4) 运算符重载(结构体作队列元素)
struct tp{
	int a, b;
};
struct cmp {
	bool operator () (const  tp a, const tp b) const {
		return a.a > b.a; //使大的优先级低，去底部，小的先出
	}
};
	priority_queue<tp,vector<tp>, cmp> s;
*/
int main()
{
    return 0;
}