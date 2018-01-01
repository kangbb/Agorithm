#关于项目的一些问题
1. 我们可能会喜欢定义常量来表示一些固定值，但是，对数组、map、vector等
使用了const,你会发现无法访问单个元素值：
eg:
```objectivec
const std::map<std::string, int> CHN_TO_NUM = {
        {"零", 0},{"一", 1},{"二", 2}, {"三", 3},{"四", 4},
        {"五", 5}, {"六", 6},{"七", 7},{"八", 8}, {"九", 9}
};
int num = CHN_TO_NUM["零"];
```
将会出现以下错误：
```objectivec
Subscripted value is not an array.
```
2. 如果对于中文使用string类型的函数substr()，需要注意的
是不同文件编码汉字所占字节数不同。也即是说，函数
```objectivec
string substr(start, len)
```
是从start开始往后截取len个字节长度的字符返回。