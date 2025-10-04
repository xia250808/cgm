# 📅 10天3D数学编程练习计划（每天4小时）

## 🧭 总体建议

*   **开发环境**：建议使用 **Visual Studio 2022**（Windows平台集成开发环境，对C++支持良好）或 **CLion**（跨平台，智能提示和CMake支持出色）。
*   **代码管理**：从一开始就使用 **Git** 管理你的代码，每天结束后提交一次进度。
*   **调试技巧**：熟练掌握调试器（设置断点、单步执行、查看变量值），这是理解和排查问题的利器。
*   **从C#到C++**：注意两者在**内存管理**（C++需手动管理或使用智能指针）、**字符串处理**（`std::string` vs C#的`String`）、**面向对象**（语法细节差异）等方面的不同。

---

## 📘 第1天：环境配置与C++基础回顾

**今日焦点**：搭建环境，重温C++基础语法，实现简单的2D点类。

*   **练习 1**：配置Visual Studio或CLion的C++开发环境，创建一个新项目，编写一个打印"Hello, 3D Math!"的程序。
*   **练习 2**：实现一个简单的`Point2D`类，包含`x`, `y`坐标。重载`+`和`-`运算符，实现点的加法和减法。
*   **练习 3**：为`Point2D`类添加一个成员函数，计算该点到另一点的距离。公式：`distance = sqrt((x2-x1)^2 + (y2-y1)^2)`。
*   **练习 4**：编写几个测试用例，验证你的点类和距离计算函数是否正确。

---

## 📘 第2天：3D向量类

**核心目标**：实现3D向量类及其基本运算。

*   **练习 1**：实现一个`Vector3`类，包含`x`, `y`, `z`成员变量。
*   **练习 2**：为`Vector3`重载运算符（`+`, `-`, `*`（标量乘）, `/`（标量除）），并实现**点积**（Dot Product）、**叉积**（Cross Product）。
*   **练习 3**：实现计算向量长度（模）的`Length()`方法和将其归一化的`Normalized()`方法。

```cpp
class Vector3 {
public:
    float x, y, z;
    
    // 构造函数
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
    
    // 向量加法
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    // 点积
    float dot(const Vector3& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
    
    // 叉积
    Vector3 cross(const Vector3& other) const {
        return Vector3(y * other.z - z * other.y,
                       z * other.x - x * other.z,
                       x * other.y - y * other.x);
    }
    
    // 向量长度
    float length() const {
        return sqrtf(x*x + y*y + z*z);
    }
    
    // 向量归一化
    Vector3 normalized() const {
        float len = length();
        if (len > 0) {
            return Vector3(x/len, y/len, z/len);
        }
        return *this;
    }
};
```

---

## 📘 第3天：矩阵类基础

**核心目标**：实现4x4矩阵类及其基本运算。

*   **练习 1**：实现一个`Matrix4x4`类，用于表示4x4矩阵。考虑使用二维数组或一维数组（16个元素）存储数据。
*   **练习 2**：实现矩阵的乘法（操作符`*`重载）。注意矩阵乘法顺序，并验证 `A * B != B * A`。
*   **练习 3**：实现矩阵的转置（Transpose）方法。

```cpp
class Matrix4x4 {
private:
    float data[4][4]; // 或 float data[16];
    
public:
    // 构造函数
    Matrix4x4();
    
    // 矩阵乘法
    Matrix4x4 operator*(const Matrix4x4& other) const;
    
    // 矩阵转置
    Matrix4x4 transpose() const;
    
    // 获取/设置元素
    float get(int row, int col) const;
    void set(int row, int col, float value);
};
```

---

## 📘 第4天：矩阵进阶运算

**核心目标**：实现矩阵的行列式和逆矩阵计算。

*   **练习 1**：实现计算矩阵行列式（Determinant）的方法（可先从3x3矩阵开始，再扩展至4x4）。
*   **练习 2**：实现求矩阵的逆（Inverse）的方法。可尝试使用伴随矩阵法（Adjugate Matrix）。
*   **练习 3**：编写测试代码，创建一个单位矩阵，验证其逆矩阵是它本身；创建一个缩放矩阵，验证其逆矩阵是否正确。

```cpp
class Matrix4x4 {
    // ... 之前的代码
    
    // 计算行列式
    float determinant() const;
    
    // 计算逆矩阵
    Matrix4x4 inverse() const;
    
    // 创建单位矩阵
    static Matrix4x4 identity();
};
```

---

## 📘 第5天：基本变换矩阵

**核心目标**：利用矩阵实现各种基本变换。

*   **练习 1**：在`Matrix4x4`类中创建静态成员函数，生成**平移矩阵**（Translation Matrix）、**缩放矩阵**（Scaling Matrix）和**旋转矩阵**（绕X、Y、轴）。
*   **练习 2**：创建一个`Vertex`结构体（包含`Vector3 position`）。使用你生成的变换矩阵，对一个顶点进行平移、缩放和旋转变换。
*   **练习 3**：实现变换的组合。验证变换顺序对结果的影响（`S * T * R * v` 和 `R * T * S * v` 的结果不同）。

```cpp
class Matrix4x4 {
    // ... 之前的代码
    
    // 创建平移矩阵
    static Matrix4x4 createTranslation(float tx, float ty, float tz);
    
    // 创建缩放矩阵
    static Matrix4x4 createScale(float sx, float sy, float sz);
    
    // 创建旋转矩阵（绕X轴）
    static Matrix4x4 createRotationX(float angle);
    
    // 创建旋转矩阵（绕Y轴）
    static Matrix4x4 createRotationY(float angle);
    
    // 创建旋转矩阵（绕Z轴）
    static Matrix4x4 createRotationZ(float angle);
};
```

---

## 📘 第6天：齐次坐标与仿射变换

**核心目标**：理解并实现齐次坐标和仿射变换。

*   **练习 1**：实现一个`Vector4`类（齐次坐标），包含`x`, `y`, `z`, `w`。思考当`w=0`和`w=1`时分别代表什么。
*   **练习 2**：修改你的矩阵乘法代码，确保它能正确处理`Vector4`。
*   **练习 3**：使用`Matrix4x4`和`Vector4`实现一个**仿射变换**（包含平移、旋转、缩放）。注意确保`w`分量在变换后正确保持为1（或0）。

```cpp
class Vector4 {
public:
    float x, y, z, w;
    
    Vector4(float x = 0, float y = 0, float z = 0, float w = 1)
        : x(x), y(y), z(z), w(w) {}
    
    // 其他运算符重载和方法
};

// 在Matrix4x4中添加与Vector4的乘法
Vector4 operator*(const Matrix4x4& matrix, const Vector4& vector);
```

---

## 📘 第7天：视图和投影矩阵

**核心目标**：实现视图和投影变换。

*   **练习 1**：实现一个**LookAt矩阵**（视图变换矩阵），用于模拟相机的位置和朝向。
*   **练习 2**：尝试实现一个简单的**正交投影矩阵**（Orthographic Projection Matrix）和**透视投影矩阵**（Perspective Projection Matrix）。
*   **练习 3**：创建一个虚拟的3D立方体（8个顶点），依次应用模型变换（缩放、旋转、平移）、视图变换和投影变换，观察顶点坐标的变化。

```cpp
class Matrix4x4 {
    // ... 之前的代码
    
    // 创建LookAt视图矩阵
    static Matrix4x4 createLookAt(const Vector3& eye, const Vector3& target, const Vector3& up);
    
    // 创建正交投影矩阵
    static Matrix4x4 createOrthographic(float left, float right, float bottom, float top, float near, float far);
    
    // 创建透视投影矩阵
    static Matrix4x4 createPerspective(float fov, float aspect, float near, float far);
};
```

---

## 📘 第8天：几何查询算法

**核心目标**：实现常见的几何查询算法。

*   **练习 1**：实现计算**点到直线距离**的函数。公式：`d = |(P - A) × (P - B)| / |B - A|`（A、B为直线上两点，P为待测点）。
*   **练习 2**：实现计算**点到平面距离**的函数。给定平面上一点和法线，或平面方程`Ax + By + Cz + D = 0`。
*   **练习 3**：实现**射线与球体的相交检测**。返回是否相交，以及相交点的距离（参数t）。

```cpp
namespace GeometryUtils {
    // 点到直线距离
    float distancePointToLine(const Vector3& point, const Vector3& linePointA, const Vector3& linePointB);
    
    // 点到平面距离
    float distancePointToPlane(const Vector3& point, const Vector3& planeNormal, const Vector3& planePoint);
    
    // 射线与球体相交检测
    bool raySphereIntersection(const Vector3& rayOrigin, const Vector3& rayDirection,
                              const Vector3& sphereCenter, float sphereRadius,
                              float& t);
}
```

---

## 📘 第9天：碰撞检测基础

**核心目标**：实现基本的碰撞检测算法。

*   **练习 1**：实现一个**AABB（轴对齐包围盒）** 类，包含`min`和`max`两个`Vector3`成员变量。
*   **练习 2**：实现判断两个AABB是否相交的函数。
*   **练习 3**：尝试实现**分离轴定理（SAT）** 用于判断两个OBB（有向包围盒）是否相交（可选，有难度）。

```cpp
class AABB {
public:
    Vector3 min;
    Vector3 max;
    
    AABB(const Vector3& min, const Vector3& max) : min(min), max(max) {}
    
    // 判断两个AABB是否相交
    bool intersects(const AABB& other) const;
};

namespace CollisionDetection {
    // AABB相交检测
    bool aabbIntersection(const AABB& a, const AABB& b);
}
```

---

## 📘 第10天：综合练习 - 变换系统

**核心目标**：整合所学知识，创建一个简单的变换系统。

*   **练习**：创建一个简单的**变换系统**。
    *   定义一个`Transform`类，包含位置（`Vector3`）、旋转（可以用欧拉角或四元数，初期可用`Vector3`）、缩放（`Vector3`）成员。
    *   为`Transform`类实现一个`GetModelMatrix()`方法，计算并返回组合后的模型矩阵（顺序通常是：缩放 -> 旋转 -> 平移）。
    *   创建多个`Transform`对象，设置不同的变换参数，计算它们的模型矩阵，并应用到一个测试顶点上，观察最终位置。
    *   **进阶**：尝试实现`Transform`之间的父子关系，子节点的变换矩阵需要乘以父节点的变换矩阵。

```cpp
class Transform {
public:
    Vector3 position;
    Vector3 rotation; // 欧拉角，单位可以是角度或弧度
    Vector3 scale;
    
    Transform* parent = nullptr;
    
    Transform(const Vector3& pos = Vector3(), 
              const Vector3& rot = Vector3(), 
              const Vector3& scl = Vector3(1, 1, 1))
        : position(pos), rotation(rot), scale(scl) {}
    
    // 获取模型矩阵
    Matrix4x4 getModelMatrix() const {
        Matrix4x4 modelMatrix = Matrix4x4::identity();
        
        // 应用缩放
        modelMatrix = modelMatrix * Matrix4x4::createScale(scale.x, scale.y, scale.z);
        
        // 应用旋转
        modelMatrix = modelMatrix * Matrix4x4::createRotationX(rotation.x);
        modelMatrix = modelMatrix * Matrix4x4::createRotationY(rotation.y);
        modelMatrix = modelMatrix * Matrix4x4::createRotationZ(rotation.z);
        
        // 应用平移
        modelMatrix = modelMatrix * Matrix4x4::createTranslation(position.x, position.y, position.z);
        
        // 如果有父节点，应用父节点的变换
        if (parent != nullptr) {
            modelMatrix = parent->getModelMatrix() * modelMatrix;
        }
        
        return modelMatrix;
    }
    
    // 设置父节点
    void setParent(Transform* newParent) {
        parent = newParent;
    }
};
```

## 💡 学习建议与资源

1.  **理解优于记忆**：每实现一个数学公式或算法，都尝试理解其几何意义。画图是很好的帮助。
2.  **测试驱动**：为每个函数编写测试用例，使用已知结果验证代码正确性。
3.  **善用调试器**：单步执行代码，观察变量值的变化，是理解矩阵乘法等复杂运算过程的最佳方式。
4.  **不要害怕重构**：随着学习的深入，你可能会对之前写的代码不满意，随时重构它。
5.  **查阅文档与社区**：遇到C++语法或标准库问题，优先查阅 **cppreference.com** 或 **Stack Overflow**。

**推荐资源**：
*   《C++ Primer》：系统学习C++语法和特性
*   《Effective C++》：了解C++最佳实践
*   GLM（OpenGL Mathematics）库源码：学习优秀的数学库实现

希望这个详细的计划能帮助你扎实地巩固3D数学基础，并顺利完成C++的编程实践！