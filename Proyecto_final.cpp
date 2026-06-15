#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib> //libreria no vista en clase la use  para limpiar pantalla con system("cls") en Windows

using namespace std;

void mostarestudiantes() {
    ifstream archivonombres("../nombres.txt");

    if (!archivonombres.is_open()) {
        cout << "Error al abrir el archivo de nombres.\n";
        return;
    }

    cout << "\n================================ LISTA DE ESTUDIANTES ================================\n";

    string carnet, nombre;

    while (getline(archivonombres, carnet, ',') && getline(archivonombres, nombre)) {
        
        ifstream archivoestudiantes("../estudiantes.txt");
        string carnetEstudiante, status = "DESCONOCIDO"; // Inicializado por si no se encuentra
        
        if (archivoestudiantes.is_open()) {
            while (getline(archivoestudiantes, carnetEstudiante, ',') && getline(archivoestudiantes, status)) {
                if (carnetEstudiante == carnet) {
                    break;
                }
            }
            archivoestudiantes.close(); 
        }

        cout << "[Carnet: " << carnet << " | Nombre: " << nombre << " | Status: " << status << "]\n";

        ifstream archivonotas("../notas.txt");
        string carnetNota, curso, nota;
        bool tieneNotas = false;
        
        if (archivonotas.is_open()) {
            cout << "   Cursos inscritos:\n";
            while (getline(archivonotas, carnetNota, ',') && getline(archivonotas, curso, ',') && getline(archivonotas, nota)) {
                if (carnetNota == carnet) {
                    cout << "     - " << curso << ": " << nota << endl;
                    tieneNotas = true;
                }
            }
            archivonotas.close(); 
        }
        
        if (!tieneNotas) {
            cout << "     (No cuenta con registros de notas)\n";
        }
        cout << "--------------------------------------------------------------------------------------\n";
    }

    archivonombres.close();
}

void buscarEstudiante() {
    ifstream archivonombres("../nombres.txt");
    if (!archivonombres.is_open()) {
        cout << "No se pudo abrir el archivo de estudiantes.\n";
        return;
    }
    
    string carnet;
    cout << "Ingrese el carnet del estudiante a buscar: ";
    cin >> carnet;
    
    string carnetfile, nombrefile;
    bool Encontrado = false;
    
    while (getline(archivonombres, carnetfile, ',') && getline(archivonombres, nombrefile)) {
        if (carnetfile == carnet) {
            Encontrado = true;
            
            ifstream archivoestudiantes("../estudiantes.txt");
            string carnetEstudiante, status = "DESCONOCIDO"; // CORREGIDO: Ahora sí guarda el estado
            
            if (archivoestudiantes.is_open()) {
                while (getline(archivoestudiantes, carnetEstudiante, ',') && getline(archivoestudiantes, status)) {
                    if (carnetEstudiante == carnet) {
                        break; // CORREGIDO: Faltaba romper el ciclo al encontrar el estado
                    }
                }
                archivoestudiantes.close(); 
            }

            cout << "\n=========================================\n";
            cout << "ESTUDIANTE ENCONTRADO:\n";
            cout << "Carnet: " << carnetfile << endl;
            cout << "Nombre: " << nombrefile << endl;
            cout << "Estado: " << status << endl;
            cout << "=========================================\n";

            ifstream archivonotas("../notas.txt");
            string carnetNota, curso, nota;
            bool tieneNotas = false;
            
            if (archivonotas.is_open()) {
                cout << "Cursos inscritos:\n";
                while (getline(archivonotas, carnetNota, ',') && getline(archivonotas, curso, ',') && getline(archivonotas, nota)) {
                    if (carnetNota == carnet) {
                        cout << "- " << curso << ": " << nota << endl;
                        tieneNotas = true;
                    }
                }
                archivonotas.close(); 
            }

            if (!tieneNotas) {
                cout << "(No cuenta con registros de notas)\n";
            }
            break; // Opcional: rompe el bucle principal de nombres ya que lo encontramos
        }
    }
    
    if (!Encontrado) {
        cout << "Estudiante no encontrado.\n";
    }
    archivonombres.close();
}

void calcularPromedio() {
    ifstream archivonotas("../notas.txt");
    if (!archivonotas.is_open()) {
        cout << "No se pudo abrir el archivo de notas.\n";
        return;
    }
    
    string carnet;
    cout << "Ingrese el carnet del estudiante para calcular su promedio: ";
    cin >> carnet;

    ifstream archivonombres("../nombres.txt");
    string carnetfile, nombrefile = "Desconocido";

    if (archivonombres.is_open()) {
        while (getline(archivonombres, carnetfile, ',') && getline(archivonombres, nombrefile)) {
            if (carnetfile == carnet) {
                break;
            }
        }
        archivonombres.close(); 
    }

    string materiafile, notafile;
    double suma = 0.0;
    int cantidadNotas = 0;
    bool Encontrado = false;
    string listaMaterias = "";

    while (getline(archivonotas, carnetfile, ',') && getline(archivonotas, materiafile, ',') && getline(archivonotas, notafile)) {
        if (carnetfile == carnet) {
            Encontrado = true;
            double nota = stod(notafile);
            suma += nota;
            cantidadNotas++;
            listaMaterias += "-" + materiafile + " : " + notafile + "\n";
        }
    }
    
    if (Encontrado && cantidadNotas > 0) {
        double promedio = suma / cantidadNotas;
        cout << "\n====================================\n";
        cout << "Estudiante: " << nombrefile << endl;
        cout << "Carnet: " << carnet << endl;
        cout << "Total de materias: " << cantidadNotas << endl;
        cout << "------------------------------------\n";
        cout << listaMaterias;
        cout << "------------------------------------\n";
        cout << "Promedio del estudiante: " << promedio << endl;
        cout << "====================================\n\n";
    } else {
        cout << "Estudiante no encontrado o sin notas registradas.\n";
    }
    archivonotas.close();
}

struct EstudianteReporte {
    string carnet;
    string nombre;
    string estado;
    double promedio;
};

void cargarDatosEstudiantes(EstudianteReporte lista[], int &cantidad) {
    cantidad = 0; 
    
    ifstream archivonombres("C:\\Users\\kenet\\OneDrive\\Documentos\\ING 3\\PROGRAMACION 1\\Proyecto_Final\\nombres.txt");
    if (!archivonombres.is_open()) {
        cout << "[ERROR] No se pudo abrir nombres.txt\n";
        return; 
    }

    string carnetBase, nombreBase;

    while (getline(archivonombres, carnetBase, ',') && getline(archivonombres, nombreBase)) {
        
        ifstream archivoestudiantes("C:\\Users\\kenet\\OneDrive\\Documentos\\ING 3\\PROGRAMACION 1\\Proyecto_Final\\estudiantes.txt");
        string carnetEst, estadoEst = "INACTIVO";
        
        if (archivoestudiantes.is_open()) {
            while (getline(archivoestudiantes, carnetEst, ',') && getline(archivoestudiantes, estadoEst)) {
                if (carnetEst == carnetBase) {
                    break; 
                }
            }
            archivoestudiantes.close();
        }

        ifstream archivonotas("C:\\Users\\kenet\\OneDrive\\Documentos\\ING 3\\PROGRAMACION 1\\Proyecto_Final\\notas.txt");
        string carnetNota, materiaNota, valorNota;
        double sumaNotas = 0.0;
        int cantidadNotas = 0;
        
        if (archivonotas.is_open()) {
            while (getline(archivonotas, carnetNota, ',') && getline(archivonotas, materiaNota, ',') && getline(archivonotas, valorNota)) {
                if (carnetNota == carnetBase) {
                    sumaNotas += stod(valorNota);
                    cantidadNotas++;
                }
            }
            archivonotas.close();
        }

        double prom = 0.0;
        if (cantidadNotas > 0) {
            prom = sumaNotas / cantidadNotas;
        }

        lista[cantidad].carnet = carnetBase;
        lista[cantidad].nombre = nombreBase;
        lista[cantidad].estado = estadoEst; 
        lista[cantidad].promedio = prom;
        
        cantidad++; 
    }
    
    archivonombres.close();
}

void ordenarPorPromedioAscendente(EstudianteReporte lista[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (lista[j].promedio > lista[j + 1].promedio) {
                EstudianteReporte aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
}

void menuReportes() {
    int opcion = 0;
    EstudianteReporte estudiantes[100]; 
    int totalEstudiantes = 0; 

    do {
        cout << "\n=========================================\n";
        cout << "           SUBMENU DE REPORTES           \n";
        cout << "=========================================\n";
        cout << "1. Estudiantes con promedio mayor o igual a 61\n";
        cout << "2. Estudiantes ordenados ascendentemente por promedio\n";
        cout << "3. Estudiante con mayor promedio\n";
        cout << "4. Cantidad de estudiantes activos\n";
        cout << "5. Regresar\n";
        cout << "=========================================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        cargarDatosEstudiantes(estudiantes, totalEstudiantes);

        switch (opcion) {
            case 1: {
                cout << "\n--- ESTUDIANTES CON PROMEDIO >= 61 ---\n";
                int encontro = 0;
                for (int i = 0; i < totalEstudiantes; i++) {
                    if (estudiantes[i].promedio >= 61.0) {
                        cout << "Carnet: " << estudiantes[i].carnet << " | Nombre: " << estudiantes[i].nombre << " | Promedio: " << estudiantes[i].promedio << "\n";
                        encontro = 1;
                    }
                }
                if (encontro == 0) {
                    cout << "No hay estudiantes con promedio mayor o igual a 61.\n";
                }
                break;
            }
            case 2: {
                cout << "\n--- ESTUDIANTES ORDENADOS ASCENDENTEMENTE ---\n";
                if (totalEstudiantes == 0) {
                    cout << "No hay datos disponibles.\n";
                } else {
                    ordenarPorPromedioAscendente(estudiantes, totalEstudiantes);
                    for (int i = 0; i < totalEstudiantes; i++) {
                        cout << "Promedio: " << estudiantes[i].promedio << " | Carnet: " << estudiantes[i].carnet << " | Nombre: " << estudiantes[i].nombre << "\n";
                    }
                }
                break;
            }
            case 3: {
                cout << "\n--- ESTUDIANTE CON MAYOR PROMEDIO ---\n";
                if (totalEstudiantes == 0) {
                    cout << "No hay datos disponibles.\n";
                } else {
                    int indiceMayor = 0;
                    for (int i = 1; i < totalEstudiantes; i++) {
                        if (estudiantes[i].promedio > estudiantes[indiceMayor].promedio) {
                            indiceMayor = i;
                        }
                    }
                    cout << "Carnet: " << estudiantes[indiceMayor].carnet << "\n";
                    cout << "Nombre: " << estudiantes[indiceMayor].nombre << "\n";
                    cout << "Promedio Maximo: " << estudiantes[indiceMayor].promedio << "\n";
                }
                break;
            }
            case 4: {
                cout << "\n--- LISTADO DE ESTUDIANTES ACTIVOS ---\n";
                int contadorActivos = 0;
                
                for (int i = 0; i < totalEstudiantes; i++) {
                    string est = estudiantes[i].estado;
                    if (est == "ACTIVO" || est == "ACTIVO\r" || est == "ACTIVO " || est == "activo" || est == "activo\r") {
                        cout << "Carnet: " << estudiantes[i].carnet 
                             << " | Nombre: " << estudiantes[i].nombre 
                             << " | Estado: " << est << "\n";
                        contadorActivos++; 
                    }
                }
                
                cout << "-----------------------------------------\n";
                cout << "Total de estudiantes en estado ACTIVO: " << contadorActivos << "\n";
                break;
            }
            case 5:
                cout << "Regresando al menu principal...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 5);
}

int main() {
    int menu;

    do {
        cout << "------Bienvenido al Sistema del Colegio------\n";
        cout << "1. Mostrar estudiantes\n";
        cout << "2. Buscar estudiante por carnet\n";
        cout << "3. Calcular promedio de estudiante\n";
        cout << "4. Insertar estudiantes activos en base de datos\n";
        cout << "5. Reportes\n";
        cout << "6. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> menu;

        switch (menu) {
            case 1:
                mostarestudiantes();
                break;
            case 2: 
                buscarEstudiante();
                break;
            case 3:
                calcularPromedio();
                break;  
            case 4:
                // Espacio reservado
                break;
            case 5:
                menuReportes();
                break;
            case 6:
                system("cls");
                cout << "Saliendo del sistema...\n";
                break;
            default:
                cout << "Ingrese una opcion valida\n";
                break;
        }
        
    } while (menu != 6);

    return 0;
}