/*输入的数字为 {1024,768}
想要从这其中获取 1024  768 这两个数字。
方法一：可以拆分字符串来获得
方法二：通过sscanf来获得

 int width, height;
 sscanf("{1024, 768}", "{%d, %d}", &width, &height);
 
 可以直接获取到width,height
 具体用法BAIDU
*/
