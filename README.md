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
	1. filter-based：基于滤波（滤波算子，迭代算子）
		- Laplacian Smooth：Laplacian operator
		- Gaussian Denoise
		- Bilateral Denoise
		- Bilateral Normal Filter
		- Fourier Transform：manifold harmonics（流形谐波）
	2. optimization-based：基于数值优化算法
		- Paper: Image smoothing via L0 gradient minmization
			- -> Mesh demoising
			- Differential Edge Laplacian Operator
			- Paper: Mesh denoising vai L0 minimization
				- 凑拉普拉斯算子：基于面积的拉普拉斯算子最好
		- Paper: Variational Mesh Denoising using Total Variation and Piecewise Constant Function Space
			- 先优化法向量，再计算顶点的位置
			- **以法向量作为中间变量，通过转化的方式来求解**
	3. data-driven：基于神经网络
		- Paper: Mesh Denoising via Cascaded Normal Regression
4. 网格参数化（parameterization、flattening、unfolding）：
	- Constraints
		- Bijective
		- Inversion-free
		- Locally injective
		- Low distortion
	- Tutte’s barycentric mapping：开网格 -> 圆盘
		1. find boundary（easily with halfedge）
		2. boundary to circle
		3. solve sparse matrix
	- Least squares conformal maps(LSCM, ASAP)
		- Conformal map：包角变换，局部是相似变换
		- LSCM：目标函数为使映射与相似映射的差值最小
			- 确定两个点：
				1. 避免平凡解（0）
				2. 去除旋转和平移带来的不唯一性
	- Angle-Based Flattening (ABF：保角变换)
		- 先计算角度，再由角度计算顶点的参数化坐标
		- 计算角度：no Linear ABF -> Linear ABF
		- 重构参数化：Reconstruct parameterization
			- Greed method：数值误差的累积
			- Least squares method：误差会均匀分布，误差会扩散到每一条边，避免了误差的累积
				- 固定一条边：去除旋转和平移带来的不唯一性
		- **以角度作为中间变量，通过转化的方式来求解***
	- As-rigid-as-possible (ARAP)


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
4. Tutte’s barycentric mapping：开网格 -> 圆盘
14. Paper: Mesh Denoising via Cascaded Normal Regression














