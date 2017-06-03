# Git使用说明

## 1. 关于项目
&#160;&#160;&#160;&#160;在git.ustclug.org上建立了项目组RobotGroup方便协作开发。

新加入的用户需要将自己的用户名邮件发送给liminkmf@mail.ustc.edu.cn，然后被加入项目组后才可以查看到项目相关的资料。

## 2. Git 教程
推荐 [Pro Git](http://iissnan.com/progit/)

## 3. 常用git命令
|Command|Usage|Note|
|-------|-----|----|
|`git init`|将当前所在目录加入版本控制|首要|
|`git clone url`|clone一个github仓库||
|`git add .`|将当前文件夹中所有文件所做修改git版本跟踪中|也可指定子目录或子文件夹|
|`git commit -m msg`|将修改commit到git仓库|msg一般描述所做修改内容|
|`git checkout <branch>`|切换到某分支,或版本节点上|`-b`参数新建分支|
|`git merge <branch1> <branch2>`|合并分支||
|`git remote add origin url`|为本地git仓库添加远程仓库|远程仓库名任意选不过一般叫`origin`|
|`git remote -v`|查看当前git仓库的远程仓库|注意`git@`和`https://`协议的区别|
|`git remote rename "name"`|修改远程仓库名||
|`git remote set-url`|为远程仓库设置地址||
|`git pull`|从远程仓库上拉取更新|注意保存自己的工作以及解决冲突|
|`git push origin master`|将master分支push到远程仓库|也即Github上，origin,master都可自己指定|

## 4. Git help
```
usage: git [--version] [--help] [-C <path>] [-c name=value]
           [--exec-path[=<path>]] [--html-path] [--man-path] [--info-path]
           [-p | --paginate | --no-pager] [--no-replace-objects] [--bare]
           [--git-dir=<path>] [--work-tree=<path>] [--namespace=<name>]
           <command> [<args>]
开始一个工作区（参见：git help tutorial）
   clone      克隆一个仓库到一个新目录
   init       创建一个空的 Git 仓库或重新初始化一个已存在的仓库

在当前变更上工作（参见：git help everyday）
   add        添加文件内容至索引
   mv         移动或重命名一个文件、目录或符号链接
   reset      重置当前 HEAD 到指定状态
   rm         从工作区和索引中删除文件

检查历史和状态（参见：git help revisions）
   bisect     通过二分查找定位引入 bug 的提交
   grep       输出和模式匹配的行
   log        显示提交日志
   show       显示各种类型的对象
   status     显示工作区状态

扩展、标记和调校您的历史记录
   branch     列出、创建或删除分支
   checkout   切换分支或恢复工作区文件
   commit     记录变更到仓库
   diff       显示提交之间、提交和工作区之间等的差异
   merge      合并两个或更多开发历史
   rebase     本地提交转移至更新后的上游分支中
   tag        创建、列出、删除或校验一个 GPG 签名的标签对象

协同（参见：git help workflows）
   fetch      从另外一个仓库下载对象和引用
   pull       获取并整合另外的仓库或一个本地分支
   push       更新远程引用和相关的对象
命令 'git help -a' 和 'git help -g' 显示可用的子命令和一些概念帮助。
查看 'git help <命令>' 或 'git help <概念>' 以获取给定子命令或概念的
帮助。
```