# 200819_DigitalGeometryProcessing

## Top Note

1. 曲面上任何函数的平滑都可以用拉普拉斯
2. 原始问题难以求解时，构建中间变量，最后再进行转换
3. 划分成低频和高频，高频在局部坐标系（n，t1，t2），低频下的操作可以达到实时，高频通过局部坐标来映射
4. Local/Global 迭代两个优化变量（普遍收敛较慢）

---

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
	1. Constraints
		- Bijective
		- Inversion-free
		- Locally injective
		- Low distortion
	2. Tutte’s barycentric mapping：开网格 -> 圆盘
		1. find boundary（easily with halfedge）
		2. boundary to circle
		3. solve sparse matrix
	3. Least squares conformal maps(LSCM, ASAP)
		- Conformal map：包角变换，局部是相似变换
		- LSCM：目标函数为使映射与相似映射的差值最小
			- 确定两个点：
				1. 避免平凡解（0）
				2. 去除旋转和平移带来的不唯一性
	4. Angle-Based Flattening (ABF：保角变换)
		- 先计算角度，再由角度计算顶点的参数化坐标
		- 计算角度：no Linear ABF -> Linear ABF
		- 重构参数化：Reconstruct parameterization
			- Greed method：数值误差的累积
			- Least squares method：误差会均匀分布，误差会扩散到每一条边，避免了误差的累积
				- 固定一条边：去除旋转和平移带来的不唯一性
		- **以角度作为中间变量，通过转化的方式来求解***
	5. As-rigid-as-possible (ARAP：尽量 isometric)
		- Paper: A Local/Global Approach to Mesh Parameterization
			- 尽量 isometric（只有平移加选择的变换）
			- 优化雅克比和旋转矩阵差的 F 范式最小
				- 交替迭代
					- 固定雅克比矩阵，优化旋转矩阵（Local）：signed SVG
					- 固定旋转矩阵，优化雅可比矩阵（Global）：最小二乘，正交方程
		- Paper:  Computing Inversion-Free Mappings by Simplex Assembly
			- Edge assembly constraints：确保三角形可以拼起来
5. 网格变形（Deformation）：
	1. Definition
		- Fixed + Deformation Region + User Handle
	2. Transformation Propagation
		- 转换扩散：handle 到 fixed 光滑插值（smooth blending）
			- 计算测地距离 or 内部拉普拉斯为零，边界为 1（迭代 or solve）
	3. Multi-Scale Deformation
		- 划分成低频和高频，在低频进行 deform 后叠加高频
		- 高频用局部坐标系来存储（n，t1，t2）
	4. Differential Coordinates
		- Gradient-Based Deformation
			- 对梯度进行 deform
			- 恢复顶点位置
		- Laplacian-Based Deformation
			- 对顶点拉普拉斯进行 deform
			- 恢复顶点位置
		- 变换插值
			- 变换矩阵成旋转和放缩（SVD）
				- 旋转 -> 四元数 -> 插值
				- 放缩 -> 插值
	5. Deformation transfer：将一个网格的变形转换到其他网格（两个网格存在一一映射）
		- 三角形不能确定唯一的仿射变换，增加一个 v1 + n 顶点
		- encode transfer（encoder-decoder？）
	6. As-Rigid-As-Possible surface deformation
		- 优化的角度，所有的变换都是旋转
			- 交替迭代（Local/Global）
			- 热启动（每次迭代以上次的迭代结果为迭代初值）
	7. Freeform Deformation • Meshless mapping
		- mesh deform -> space deform
		- Lattice-Based Freeform Deformation
			- 基于 B-spline
		- Cage-Based Freeform Deformation
			- 外部变换传递到内部：重心坐标（变换前后的 GBC 不变）
	8. Volumetric Deformation • Tetrahedral mapping
		- no mention
	9. 总结
		1. handle-based deformation
		2. cage-based deformation
		3. skeleton-based deformation
6. 重心坐标（Barycentric）：
	1. Introduction
		- 非负性
		- 求和为1
		- reproduction，可以由顶点的坐标组合构造出所有的内点
	2. Barycentric coordinates on convex polygons
		- Generalized barycentric coordinates（GBC）
		- 形式和双线性插值相同
	3. Inverse bilinear coordinates
		- 矩形上的重心坐标
	4. Mean value coordinates（MVC）
		- MVC 公式
		- Motivation of MVC：逼近 harmonic maps（调和映射，拉普拉斯为零）
	5. Harmonic Coordinates
	6. A general construction
		- Skeleton-subspace deformation
			- Linear blend skinning
		- Paper: Bounded Biharmonic Weights for Real-Time Deformation
			- Points-handles：局部微调变换
			- Bones-handles：局部刚性变换
			- Cages-handles：整体变换
			- 有局部性，局部变换不会扩散到其他顶点，不会有负值和反转
7. 网格修复（Repair）（**介绍为主**）：
	1. Definitions
		- Application dependent（only display or FEM）
		- Artifacts 产生	
			- 激光扫描产生
			- Non-uniform rational B-spline（NURBS） -> Marching Cube -> Mesh 产生
			- PointCloud -> Mesh 产生
	2. Defects and flaws
		1. 孤立点和悬挂边
		2. 奇异边
		3. 奇异点
		4. 拓扑噪声（虚假环炳）
		5. 法线方向（面朝向）不一致
		6. 补洞（具有主观性，模糊性，不确定性）
		7. 狭缝（分裂或重叠）
		8. 退化三角形
		9. 自相交（穿模）
		10. 锋利的倒角
		11. 数据噪声
	3. Upstream and Downstream applications
		- 根据 Upstream 确定 Artifacts 类型
		- 根据 Downstream 确定需要修复到什么程度
	4. Types of input
		- Registered range scans（注册范围扫描）
		- Fused range scans（融合范围扫描）
		- Triangle soups（一坨三角形）
		- Triangulated NURBS patches（多个 NURB 单独三角化后连接到一起）
		- Contoured meshes（体素提取获得的网络）
		- Badly meshed manifolds（质量差的三角形网格）
	5. Approaches
		- Volumetric algorithms（体素算法：Mesh -> grid）
8. 映射（Mapping）：
	1. Introduction
		- Mappings
			- Mesh-based mapping
			- Meshless mapping
		- Applications
			- Parameterization
			- Deformation
			- Mesh Improvement
			- Compatible remeshing（surface mapping）
		- Basic requirements(Foldover-free: det(J)>0)
		- Basic goal (As Rigid As Possible, As similar as Possible)
			- Distortion of J is about its eigenvalue: min D(f)
	2. Maintenance-based methods
		- Paper: Most-Isometric ParameterizationS (MIPS，满足约束的不好解 -> 满足约束的好解)
		1. 初始有效映射
		2. 随机选择顶点
		3. 牛顿迭代
		4. 重复 2-3
		5. 输出有效映射
	3. Bounded distortion methods
		- Paper: Bounded distortion mapping spaces for triangular meshes
	4. Representation-based method
		- Paper: Computing inversion-free mappings by simplex assembly




---

## 作业

1. 网格表示：两点最短路径 & 最小生成树
2. 离散微分几何：可视化平均曲率和高斯曲率（梯度）
3. 网格平滑：Paper: Bilateral Normal Filtering for Mesh Denoising
	- 迭代计算新的面 normal
	- 恢复顶点位置
		- gauss-seidel 迭代 or
		- 解线性方程
	- 保持三角网格的体积
4. 网格参数化：Tutte’s barycentric mapping
	- 开网格 -> 圆盘（uniform laplacian）
5. 网格参数化：Paper: A Local/Global Approach to Mesh Parameterization
6. 网格变形：Paper: As-Rigid-As-Possible surface deformation
7. 重心坐标：Mean value coordinates（Tutte’s barycentric mapping
	- 开网格 -> 圆盘（MVC laplacian））
14. 网格平滑：Paper: Mesh Denoising via Cascaded Normal Regression














