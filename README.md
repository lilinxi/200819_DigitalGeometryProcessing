# 200819_DigitalGeometryProcessing

## 课程

1. 网格表示：
	1. 点云
	2. 符号距离场
	4. 隐函数
	5. Grid 网格：八叉树，
	5. Mesh 网格：半边结构
2. 离散微分几何：
	1. 局部平均区域
	2. 法向量
	3. 梯度
	4. 拉普拉斯算子
		- uniform
		- cot
	5. 曲率
		- 平均曲率：(max+min)/2
		- 高斯曲率：max x min
3. 网格平滑：
	1. filter-based：给予滤波
		- Laplacian Smooth：Laplacian operator
		- Gaussian Denoise
		- Bilateral Denoise
		- Bilateral Normal Filter
		- Fourier Transform：manifold harmonics（流形谐波）
	2. optimization-based：基于优化算法
		- Paper: Image smoothing via L0 gradient minmization
			- -> Mesh demoising
			- Differential Edge Laplacian Operator
			- Paper: Mesh denoising vai L0 minimization
				- 凑拉普拉斯算子：基于面积的拉普拉斯算子最好
		- Paper: Variational Mesh Denoising using Total Variation and Piecewise Constant Function Space
			- 先优化法向量，再计算顶点的位置
	3. data-driven：基于神经网络
		- Paper: Mesh Denoising via Cascaded Normal Regression

---

## 作业

1. 两点最短路径 & 最小生成树
2. 可视化平均曲率和高斯曲率（梯度）
3. Paper: Bilateral Normal Filtering for Mesh Denoising
	- 迭代计算新的面 normal
	- 恢复顶点位置
		- gauss-seidel 迭代 or
		- 解线性方程
	- 保持三角网格的体积
14. Paper: Mesh Denoising via Cascaded Normal Regression












