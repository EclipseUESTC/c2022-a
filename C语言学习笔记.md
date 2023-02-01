# C语言学习笔记

# 记录你学习过程中的所见所思！酸甜苦辣！

# 看什么看！ 赶紧填坑啊！ 
---
# Let's get started!

# 文件函数
1. 打开文件
    `FILE *fp = fopen("*address*","r");`
2. 关闭文件
    `fclose(fp);`
3. 读取一行文件
   `char str[200];`
   `fgets(str,200,fp);`
4. 文件末尾标志：`EOF`
5. 读取单字符
   `char ch = fgetc(fp);`