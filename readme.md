## 关于去除标题栏,保留阴影
### 参考
* [微软文档](https://learn.microsoft.com/zh-cn/windows/win32/dwm/customframe#appendix-c-hittestnca-function)
提供命中判定
* [StackOverflow&网友](https://stackoverflow.com/questions/22165258/how-to-create-window-without-border-and-with-shadow-like-github-app/44489430#44489430)
提供去标题和阴影保留思路
### 具体
1. 让窗体具有WS_CAPTION
2. 将非工作区扩展到工作区内
```c
MARGINS margins = {1};
DwmExtendFrameIntoClientArea(hwnd, &margins);
```
3. 处理WM_NCCALCSIZE消息,但是不转发
4. 处理WM_NCHITTEST,修正非工作区的命中测试