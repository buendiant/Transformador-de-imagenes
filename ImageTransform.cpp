#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

// Convierte imagen a vector de píxeles (solo para información)
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

// Aplica una transformación usando matriz 3x3 (tu filtro original)
Mat applyTransformation(const Mat& img, const Matx33f& transform) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3f pixel = img.at<Vec3b>(i, j);   // B, G, R
            Vec3f transformed = transform * pixel;

            for (int k = 0; k < 3; k++)
                transformed[k] = std::min(std::max(transformed[k], 0.0f), 255.0f);

            result.at<Vec3b>(i, j) = Vec3b(transformed);
        }
    }
    return result;
}

// ---------------- Filtros extra ------------------

// Filtro cálido (más rojizo/naranja)
Mat applyWarmFilter(const Mat& img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3b p = img.at<Vec3b>(i, j); // B, G, R

            int b = p[0];
            int g = p[1];
            int r = p[2];

            b = saturate_cast<uchar>(b * 0.9f);
            g = saturate_cast<uchar>(g * 1.05f);
            r = saturate_cast<uchar>(r * 1.2f);

            result.at<Vec3b>(i, j) = Vec3b(b, g, r);
        }
    }
    return result;
}

// Filtro frío (más azulado)
Mat applyCoolFilter(const Mat& img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3b p = img.at<Vec3b>(i, j); // B, G, R

            int b = p[0];
            int g = p[1];
            int r = p[2];

            b = saturate_cast<uchar>(b * 1.2f);
            g = saturate_cast<uchar>(g * 0.95f);
            r = saturate_cast<uchar>(r * 0.85f);

            result.at<Vec3b>(i, j) = Vec3b(b, g, r);
        }
    }
    return result;
}

// Filtro sepia
Mat applySepiaFilter(const Mat& img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3b p = img.at<Vec3b>(i, j); // B, G, R

            float b = p[0];
            float g = p[1];
            float r = p[2];

            float newR = 0.393f * r + 0.769f * g + 0.189f * b;
            float newG = 0.349f * r + 0.686f * g + 0.168f * b;
            float newB = 0.272f * r + 0.534f * g + 0.131f * b;

            result.at<Vec3b>(i, j) = Vec3b(
                saturate_cast<uchar>(newB),
                saturate_cast<uchar>(newG),
                saturate_cast<uchar>(newR)
            );
        }
    }
    return result;
}

// Filtro verde tipo "Matrix"
Mat applyGreenFilter(const Mat& img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3b p = img.at<Vec3b>(i, j); // B, G, R

            int b = p[0];
            int g = p[1];
            int r = p[2];

            b = saturate_cast<uchar>(b * 0.8f);
            g = saturate_cast<uchar>(min(255.0f, g * 1.5f));
            r = saturate_cast<uchar>(r * 0.6f);

            result.at<Vec3b>(i, j) = Vec3b(b, g, r);
        }
    }
    return result;
}

// Filtro raro (efecto psicodélico/glitch)
Mat applyWeirdFilter(const Mat& img) {
    Mat result = img.clone();

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            Vec3b p = img.at<Vec3b>(i, j); // B, G, R

            float b = p[0];
            float g = p[1];
            float r = p[2];

            // Mezcla rara:
            // - Azul: inversión del rojo
            // - Verde: promedio de todos
            // - Rojo: diferencia fuerte entre azul y verde
            float newB = 255.0f - r;
            float newG = (b + g + r) / 3.0f;
            float newR = fabs(b - g) * 1.5f; // realza diferencias

            // Un poquito de contraste
            newR = min(255.0f, max(0.0f, newR));
            newG = min(255.0f, max(0.0f, newG));
            newB = min(255.0f, max(0.0f, newB));

            result.at<Vec3b>(i, j) = Vec3b(
                saturate_cast<uchar>(newB),
                saturate_cast<uchar>(newG),
                saturate_cast<uchar>(newR)
            );
        }
    }
    return result;
}

// ---------------------- main ----------------------

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
        -1, 0, 255,
        0, -1, 255,
        0, 0, 1
    );

    // Calcular inversa (solo informativo)
    Matx33f inverseTransform = transform.inv();
    cout << "Matriz inversa:\n" << Mat(inverseTransform) << endl;

    // --------- Menú de filtros ----------
    cout << "\nElige el filtro que deseas aplicar:\n";
    cout << "1. Filtro original (invertir colores con matriz)\n";
    cout << "2. Filtro calido\n";
    cout << "3. Filtro frio\n";
    cout << "4. Filtro sepia\n";
    cout << "5. Filtro verde tipo Matrix\n";
    cout << "6. Filtro extraño\n";
    cout << "0. Sin filtro (solo mostrar original)\n";
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;

    Mat resultado;
    string nombreVentana = "Resultado";
    string nombreArchivo = "salida.jpg";

    switch (opcion) {
    case 1:
        resultado = applyTransformation(img, transform);
        nombreVentana = "Invertida (matriz)";
        nombreArchivo = "salida_invertida.jpg";
        break;
    case 2:
        resultado = applyWarmFilter(img);
        nombreVentana = "Filtro calido";
        nombreArchivo = "salida_calida.jpg";
        break;
    case 3:
        resultado = applyCoolFilter(img);
        nombreVentana = "Filtro frio";
        nombreArchivo = "salida_fria.jpg";
        break;
    case 4:
        resultado = applySepiaFilter(img);
        nombreVentana = "Filtro sepia";
        nombreArchivo = "salida_sepia.jpg";
        break;
    case 5:
        resultado = applyGreenFilter(img);
        nombreVentana = "Filtro verde";
        nombreArchivo = "salida_verde.jpg";
        break;
    case 6:
        resultado = applyWeirdFilter(img);
        nombreVentana = "Filtro raro";
        nombreArchivo = "salida_rara.jpg";
        break;
    case 0:
    default:
        cout << "Mostrando solo la imagen original.\n";
        resultado = img.clone();
        nombreVentana = "Original";
        nombreArchivo = "salida_original.jpg";
        break;
    }

    // Mostrar y guardar
    imshow("Original", img);
    imshow(nombreVentana, resultado);
    imwrite(nombreArchivo, resultado);

    cout << "Imagen guardada como: " << nombreArchivo << endl;

    waitKey(0);
    return 0;
}
