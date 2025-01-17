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
9. 多立方体生成（PolyCube）（**介绍为主**）：
	1. Definition
		- Tetrahedral Mesh -> PolyCube -> All-Hex Mesh
	2. Deformation-based method
		- All-Hex Mesh Generation via Volumetric PolyCube Deformation
	3. Voxel-based method
		- Optimizing PolyCube domain construction for hexahedral remeshing
		1. compute polycube
		2. compute mesh-polycube mapping
	4. Cluster-based method
		- PolyCut: Monotone Graph-Cuts for PolyCube Base-Complex Construction
	5. Generalized PolyCube
10. 表面映射（Surface Mapping）（**介绍为主**）：
	1. Definition
		- one-to-one mapping between surfaces
	2. Application
		1. Morphing（变形）
		2. Attribute transfer
	3. Algorithms
		- Common base domain
			- A -> C <- B(都转化到一个简单的网格表面)
		- Parameterization-based method
			- A -> C <- B(都转化到一个边界相同的参数域)
			1. cutting path
			2. compute theta, phi
			3. bijection lifting
11. 形状插值（Morphing, shape interpolation）：
	1. Definition
		- (Source, Target) -> interpolation
	2. Angle, length, area, volume, and curvature
		- Example-Driven Deformations Based on Discrete Shells
		- 基于无限小的采样
	3. Affine transformation
		- As-Rigid-As-Possible Shape Interpolation
		- 基于仿射变换的插值
			- 简单插值
			- SVD 插值
			- RS 插值（对极分解：rotation & scaler）（**效果最好**）
	4. Data-driven morphing（no mention）
		- A Data-Driven Approach to Realistic Shape Morphing
		- Data-Driven Shape Interpolation and Morphing Editing
	5. 点云注册/对齐（Point set registration）
		- ICP：两步迭代
			1. 寻找最近的对应点
			2. 计算误差最小的刚体变换
			3. 迭代 1-2
12. 纹理映射生成（Atlas generation）：
	1. Definition
		- Requires defining a mapping from the model space to the texture space
	2. Mesh cutting
		1. Point -> Paths
			- Paper: Geometry Images
		2. Segmention
			- Paper: D-Charts: Quasi-Developable Mesh Segmentation
	3. Chart parameterization
		- Bijective, low distortion
		- Scaffold（脚手架)
			- Paper: Simplicial Complex Augmentation Framework for Bijective Maps
	4. Chart packing（略）
	5. Paper: Atlas Refinement with Bounded Packing Efficiency
		- Packing Efficiency
			- Low distortion
			- Consistent orientation
			- Overlap free
			- Low boundary length
		- Atlas Refinement Pipeline
			1. Overloap Paramterization ->
			2. Axis-Aligned Structure ->
			3. Distortion Reduction
13. 网格简化（Simplification）：
	1. Definition
		- 曲率保持 or 曲率移除（保持高曲率的点，或移除高曲率的点）
	2. Local operations
		1. 点移除
		2. 边坍缩
		3. 半边坍缩（会产生非法的拓扑结构）
	3. Quadric error metric(QEM)
		- 计算每个点的二次误差度量
		- 每个边有一个二次误差度量
		- 每次迭代移除误差最小的边
		- 重新计算涉及到的边的二次误差度量
	4. Variational shape approximation
		- Paper: Variational shape approximation (VSA)
		- 用大面片替换若干小面片
14. 球面参数化：
	1. Definition & Applications
		- 零亏格曲面 -> 球面
	2. Hierarchical method
		- Paper: Advanced Hierarchical Spherical Parameterizations
			- Flat-to-extrusive decimation strategy：先移除接近平面，再移除高曲率平面
			1. triangle mesh
			2. Decimation 简化，去掉高曲率
				- Curvature error metric (CEM)
			3. Refinement 精炼，按照原来的顺序逆序将点加回来
			4. triangular sphere
	3. Two hemispheres
		- 先映射到两个圆盘上，再映射到两个半球上（用球极投影融合，或者直接融合）
	4. Curvature flow（ricci flow）
		- no mention
15. 方向场（Directional Field）：
	1. Introduction
		- magnitude & direction
        - Vector fields
        - Cross fields
        - Frame fields
	2. Discretization
		- 切空间：
			- 面的切空间是法向量
			- 点和边的切空间是加权平均的法向量
		- index：转一圈的角度差除以 2pi，不等于 0 的为奇异点
	3. Representation
		- 局部坐标系 + Angle-based = 1-direction field
		- 局部坐标系 + Angle-based-N-Symmetry = N-symmetry-dicection field
	4. Objectives and Constraints
        - Objectives：Fairness（光滑）
        - Constraints：Alignment（对齐）
        - 可积场是无旋的
        - Paper: Frame Fields: Anisotropic and Non-Orthogonal Cross Fields
16. 重新网格化：
    1. Introduction
        - 网格质量提升且与原网格接近
        - 网格质量提升修复的是非拓扑的问题
        - 优化：采样密度，三角形正规化
        - 保持：Element alignment and orientation
    2. Isotropic remeshing
        - Incremental Remeshing:
            - Edge collapse
            - Edge split
            - Edge filp
            - Vertex reclocation
            - Project to surface（CGAL: AABB tree）
        - Error-bounded method: Hausdorff distance
    3. Anisotropic remeshing
        - no mention
17. Delaunay 三角化：
    1. Introduction
        - Convex hull：凸包
            +  Carathéodory’s Theorem：通过计算凸包的点来计算凸包，O(N^4)
                *  边界点不在任何其他三个点形成的三角形内部
            +  The Separation Theorem：通过计算凸包的边来计算凸包，O(N^3)
                *  所有点都在边界边的一侧
        - Triangulation
        - Delaunay triangulation
            + Delaunay Triangulation（空圆性：任何三角形的外接圆内部不包含其他点）
        - The Lawson Flip algorithm
            1. 初始化三角化
            2. 不满足空圆性的边进行 flip
                - 通过 lifting map 进行空圆性的判断
    2. Properties
        - Empty Circle：空圆性
        - Maximize the minimum angle：最大化最小角
    3. Optimal Delaunay triangulation
        - 改变顶点位置，使得最小角进一步最大化
        - 优化 flip map 的三菱锥和抛物面的体积差
18. Voronoi 图：
    1. Introduction
        - Post Office Problem
        - Voronoi Diagram
            + Voronoi Cell：每个区域里面距离凸多边形的点最近
    2. Duality
    	- Voronoi 图 和 Delaunay 三角化，是相互对偶的关系
    3. Centroidal Voronoi tessellations (CVT) 
        - Definition
        - Applications
        - Algorithms

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
8. 形状插值：基于仿射变换的 RS 插值
9. 网格简化：边坍缩算法
10. 方向场：复数多项式的形式优化 Cross fields，四边形网格生成
11. 重新网格化：Incremental Remeshing（CGAL: AABB tree）
12. Delaunay 三角化：The Lawson Flip algorithm + Optimal Delaunay triangulation
13. Voronoi 图：Lloyd iteration 在网格简化上的实现：Variational shape approximation (VSA)
14. 网格平滑：Paper: Mesh Denoising via Cascaded Normal Regression














