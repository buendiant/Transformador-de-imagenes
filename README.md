# 🖼️ ImageTransform

**ImageTransform** es una aplicación en **C++** que permite cargar una imagen y aplicar **transformaciones personalizadas mediante matrices de color**.  
El proyecto utiliza **OpenCV** para la manipulación de imágenes y está configurado con **CMake** para una fácil compilación en **CLion** o **Visual Studio**.

---

## 🚀 Características

- Carga de imágenes desde una ruta personalizada ingresada por el usuario.  
- Conversión de la imagen a un vector de píxeles (`std::vector<cv::Vec3b>`).  
- Aplicación de transformaciones de color usando matrices 3x3.  
- Visualización de la imagen original y la transformada.  
- Ejemplo inicial: inversión de colores.  

---

## 🧩 Requisitos

### 🔹 Dependencias

- **OpenCV 4.x**  
- **CMake ≥ 3.20**  
- **vcpkg** (para gestionar OpenCV)  
- **Compilador compatible con C++17 o superior**  
  *(recomendado: MSVC, MinGW o Clang)*  

---

### 🔹 Instalación de OpenCV con vcpkg

Ejecutar en **PowerShell** o **CMD**:

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.ootstrap-vcpkg.bat
vcpkg install opencv:x64-windows
```

---

## ⚙️ Configuración del proyecto

1. **Clona este repositorio:**
   ```bash
   git clone https://github.com/tu-usuario/ImageTransform.git
   cd ImageTransform
   ```

2. **Crea una carpeta de compilación:**
   ```bash
   mkdir build
   cd build
   ```

3. **Ejecuta CMake:**
   ```bash
   cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/tuUsuario/vcpkg/scripts/buildsystems/vcpkg.cmake
   ```

4. **Compila el proyecto:**
   ```bash
   cmake --build .
   ```

---

## ▶️ Ejecución

Ejecuta el programa desde **CLion** o desde la **consola**:

```bash
./ImageTransform
```

El programa pedirá la ruta de la imagen:

```
Ingrese la ruta completa de la imagen (ejemplo: C:/Users/tuUsuario/imagen.jpg):
```

Al cargar la imagen, mostrará dos ventanas:

- **Original**  
- **Transformada (colores invertidos)**  

Presiona cualquier tecla para cerrar.

---

## 🧠 Estructura del proyecto

```
ImageTransform/
├── CMakeLists.txt
├── main.cpp
├── imagen.jpg              # Imagen de prueba (opcional)
├── cmake-build-debug/      # Carpeta de compilación generada por CLion
└── README.md
```

---

## 👨‍💻 Autor

**Juan Antonio Buendía Sánchez**  
Estudiante de Ingeniería de Sistemas — Universidad EAFIT  
Apasionado por el desarrollo en C++, visión por computadora y procesamiento digital de imágenes.
