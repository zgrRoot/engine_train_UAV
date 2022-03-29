# 工程训练无人机视觉代码
---
 
## 介绍  
本代码是吉林大学TARS-GO战队Robomaster2020赛季步兵视觉算法，主要模块分为**roi区域识别**、**SVM字母识别**、**特征识别**、**相机驱动**及**串口/CAN通信**。  

---
## 目录
* [1. 功能介绍](#1功能介绍)
* [2. 实现方式](#2实现方式)
* [3. 算法思路](#3算法思路)
* [4. 自主避障](#4自主避障)
* [5. 比赛过程](#5比赛过程)

---
## 1.功能介绍
|模块     |功能     |
| ------- | ------ |
|SVM| SVM以及KNN识别英文字母 |
|map match| 划分并初步检测roi区域 |
|solve| 无人机运行方向指令变换 |
|相机驱动| 大恒相机SDK封装，实现相机参数控制及图像采集 |
|Can| 串口/CAN通信 |
---
## 2.实现方式
1.思路：<br>
无人机从H区起飞，（上升到2-3m的位置对全地图进行初步定位和区域识别），按照规划好的路线飞行到指定区域周围，利用特征识别和机器学习进行具体区域的甄别，以及区域中心的定位，（A区域靶环进行靶环轮廓分层中心识别）。
息。  

2.实现途径：<br>
无人机装载树莓派/机载计算机，CSI摄像头；
Opencv实现视觉识别

<div align=center>** 地图 **</div>  

<div align=center>
<img src="https://github.com/zgrRoot/enginetrain_uav/raw/master/map.png" width = "600" alt="地图"/>
</div>  

---
## 3.算法思路
### 视觉识别算法思路：
首先，特征分析：场地分为:<br>
H区：矩形准备区域，正方形的区域特征，有字母H；<br>
A区：靶环投放区，同心圆区域，需要提高区域中心点的识别能力；<br>
B区：圆形字母区域，有既定贴图，圆形，英文字母；<br>
C区：圆形图像区域，有既定贴图，圆形，简易图形；<br>
实现：B、C区域主要通过机器学习来实现，通过官方给出的贴图制作图像数据集，通过SVM/神经网络分层，来对图像进行分类，对这两个区域进行甄别，以及区域中心点的判定；<br>
H区，识别场中矩形区域，利用长宽比为1，以及中心字母H,进一步筛选出起降区；<br>
A区：用同心圆识别来定位A区，通过对于同心圆轮廓特征以及A区完整图像的分析来确定靶心位置；<br>
利用单目测距的方法来确定无人机的移动距离；

---
## 4.自主避障
途中利用slam定位建图导航避障，传感器辅以路线规划对障碍物进行规避。（前置摄像头对于场地区域内的灯柱和建筑进行识别）。<br>
通过slam深度视觉建图来对场地信息进行分析，无人机提取环境信息；<br>
通过传感器（TOF红外测距等）来对（墙体和灯柱）障碍物进行距离检测，辅以无人机路线规划来完成无人机的自动避障；<br>
考虑到可能由于灯光强度不定，障碍物表面材质不定，以及规避安全网有可能失败，很有可能干扰无人机的避障能力，设置一个前置镜头对飞行图像中可能遇到的障碍（安全网、建筑物、灯柱）进行特征识别，来提高避障的成功效果。<br>

---
## 5.比赛过程
无人机装好物料后在H区准备起飞，悬停片刻后开始飞行：
### 评分方法：
1.完成运送路线：<br>
完成从H到A越过墙体到达B，在从B区越过灯柱到达C最后飞越障碍回到H的完整路径。<br>
2.完成三次越障：<br>
从障碍物上方飞过，不触碰障碍物和安全网；<br>
3.完成货物的投放：<br>
货物投放到指定区域，运送途中不发生掉落；<br>
B,C区将货物投放到区域轮廓内，A区货物投放位置距离靶心越近得分越高；
