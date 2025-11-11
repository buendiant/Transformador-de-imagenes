#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

// Convierte imagen a vector de píxeles
vector<Vec3b> imageToVector(const Mat& img) {
    vector<Vec3b> pixels;
    pixels.reserve(img.rows * img.cols);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            pixels.push_back(img.at<Vec3b>(i, j));
        }
    }
    return pixels;
}

// Aplica una transformación usando matriz 3x3
Mat applyTransformation(const Mat& img, const Matx33f& transform) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3f pixel = img.at<Vec3b>(i, j);
            Vec3f transformed = transform * pixel;

            for (int k = 0; k < 3; k++)
                transformed[k] = std::min(std::max(transformed[k], 0.0f), 255.0f);

            result.at<Vec3b>(i, j) = Vec3b(transformed);
        }
    }
    return result;
}

int main() {
    string ruta;
    cout << "Ingrese la ruta completa de la imagen (ejemplo: C:/Users/tuUsuario/imagen.jpg): ";
    getline(cin, ruta);

    Mat img = imread(ruta);
    if (img.empty()) {
        cerr << "Error: No se pudo cargar la imagen. Verifique la ruta." << endl;
        return -1;
    }

    cout << "✅ Imagen cargada correctamente (" << img.cols << "x" << img.rows << ")." << endl;

    vector<Vec3b> pixels = imageToVector(img);
    cout << "Total de píxeles: " << pixels.size() << endl;

    // Matriz de transformación (invertir colores)
    Matx33f transform = Matx33f(
        -1,  0, 255,
         0, -1, 255,
         0,  0,   1
    );

    // Calcular inversa
    Matx33f inverseTransform = transform.inv();
    cout << "Matriz inversa:\n" << Mat(inverseTransform) << endl;

    Mat transformed = applyTransformation(img, transform);

    imshow("Original", img);
    imshow("Transformada", transformed);
    imwrite("salida.jpg", transformed);

    waitKey(0);
    return 0;
}
