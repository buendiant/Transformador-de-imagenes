# 🖼️ ImageTransform

**ImageTransform** es una aplicación en C++ que permite cargar una imagen y aplicar transformaciones personalizadas mediante matrices de color.  
El proyecto utiliza **OpenCV** para la manipulación de imágenes y está configurado con **CMake** para una fácil compilación en CLion o Visual Studio.

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
- [OpenCV 4.x](https://opencv.org/)
- [CMake ≥ 3.20](https://cmake.org/)
- [vcpkg](https://github.com/microsoft/vcpkg) (para gestionar OpenCV)
- Compilador compatible con C++17 o superior  
  (recomendado: MSVC, MinGW o Clang)

### 🔹 Instalación de OpenCV con vcpkg

Ejecutar en powershell o CMD

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

.\bootstrap-vcpkg.bat
vcpkg install opencv:x64-windows

⚙️ Configuración del proyecto

Clona este repositorio:

git clone https://github.com/tu-usuario/ImageTransform.git
cd ImageTransform


Crea una carpeta de compilación:

mkdir build
cd build


Ejecuta CMake:

cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/Users/tuUsuario/vcpkg/scripts/buildsystems/vcpkg.cmake


Compila el proyecto:

cmake --build .

▶️ Ejecución

-Ejecuta el programa desde CLion o desde consola:

./ImageTransform


-El programa pedirá la ruta de la imagen:

Ingrese la ruta completa de la imagen (ejemplo: C:/Users/tuUsuario/imagen.jpg):


-Al cargar la imagen, mostrará dos ventanas:

 .Original

 .Transformada (colores invertidos)

Presiona cualquier tecla para cerrar.

🧠 Estructura del proyecto
ImageTransform/
├── CMakeLists.txt
├── main.cpp
├── imagen.jpg              # Imagen de prueba (opcional)
├── cmake-build-debug/      # Carpeta de compilación generada por CLion
└── README.md
