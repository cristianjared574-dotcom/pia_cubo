#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstdio>

using namespace std;

struct Tripla {
    double a, b, c;
};

double redondear3(double val, bool activar) {
    if (!activar) return val;
    return round(val * 1000.0) / 1000.0;
}

void dibujar_circuito_inicial(double V, double R_AE, double R_EF, double R_EH,
                              double R_AH, double R_HF, double R_AD, double R_DH,
                              double R_DC, double R_FG, double R_HG, double R_HC, double R_CG) {
    char sV[16], sAE[16], sEF[16], sEH[16], sAH[16], sHF[16], sAD[16], sDH[16], sDC[16], sFG[16], sHG[16], sHC[16], sCG[16];
    snprintf(sV,  sizeof(sV),  "%6.1fV", V);
    snprintf(sAE, sizeof(sAE), "%5.1f", R_AE);
    snprintf(sEF, sizeof(sEF), "%5.1f", R_EF);
    snprintf(sEH, sizeof(sEH), "%5.1f", R_EH);
    snprintf(sAH, sizeof(sAH), "%5.1f", R_AH);
    snprintf(sHF, sizeof(sHF), "%5.1f", R_HF);
    snprintf(sAD, sizeof(sAD), "%5.1f", R_AD);
    snprintf(sDH, sizeof(sDH), "%5.1f", R_DH);
    snprintf(sDC, sizeof(sDC), "%5.1f", R_DC);
    snprintf(sFG, sizeof(sFG), "%5.1f", R_FG);
    snprintf(sHG, sizeof(sHG), "%5.1f", R_HG);
    snprintf(sHC, sizeof(sHC), "%5.1f", R_HC);
    snprintf(sCG, sizeof(sCG), "%5.1f", R_CG);

    cout << "\n=================================================================\n";
    cout << "                   DIAGRAMA DEL CIRCUITO INICIAL                 \n";
    cout << "=================================================================\n\n";
    cout << "                            [E]\n";
    cout << "                           / | \\\n";
    cout << "                 " << sAE << "    /  |  \\    " << sEF << "\n";
    cout << "                         /   |   \\\n";
    cout << "                        / " << sEH << "  \\\n";
    cout << "                       /     |     \\\n";
    cout << "         +-----------[A]    [H]    [F]\n";
    cout << "         |            |\\    / \\    /|\n";
    cout << "         |            | \\" << sAH << " " << sHF << "/ |\n";
    cout << "         |            |  \\ /   \\ /  |\n";
    cout << "         |      " << sAD << " |   X     X   | " << sFG << "\n";
    cout << "         |            |  / \\   / \\  |\n";
    cout << "      (  +  )         | /" << sDH << " " << sHG << "\\ |\n";
    cout << "     " << sV << "         |/    \\ /    \\|\n";
    cout << "      (  -  )        [D]    [H']   [G]\n";
    cout << "         |             \\     |     /\n";
    cout << "         |              \\ " << sHC << "  /\n";
    cout << "         |               \\   |   /\n";
    cout << "         |       " << sDC << "    \\  |  /    " << sCG << "\n";
    cout << "         |                 \\ | /\n";
    cout << "         +------------------[C]\n\n";
    cout << "  Nota: [H] y [H'] representan el mismo nodo central H.\n";
    cout << "=================================================================\n";
}

void dibujar_circuito_final(double V, double Rq, double Ix) {
    char sV[16], sRq[16], sIx[16];
    snprintf(sV,  sizeof(sV),  "%6.1f V", V);
    snprintf(sRq, sizeof(sRq), "%6.3f ohm", Rq);
    snprintf(sIx, sizeof(sIx), "%6.4f A", Ix);

    cout << "\n=================================================================\n";
    cout << "                 CIRCUITO EQUIVALENTE REDUCIDO                   \n";
    cout << "=================================================================\n\n";
    cout << "          Ix = " << sIx << "\n";
    cout << "         +---------->---------+\n";
    cout << "         |                    |\n";
    cout << "         |                    /\n";
    cout << "      (  +  )                 \\\n";
    cout << "    " << sV << "               /  Rq10 = " << sRq << "\n";
    cout << "      (  -  )                 \\\n";
    cout << "         |                    /\n";
    cout << "         |                    |\n";
    cout << "         +--------------------+  (Nodo C)\n\n";
}

Tripla y_a_delta(double r1, double r2, double r3, const string& nombre_paso, bool redondear) {
    double num = (r1 * r2) + (r2 * r3) + (r3 * r1);
    double ra = redondear3(num / r1, redondear);
    double rb = redondear3(num / r2, redondear);
    double rc = redondear3(num / r3, redondear);

    cout << "\n--- " << nombre_paso << " (Estrella Y -> Delta) ---\n";
    cout << fixed << setprecision(3);
    cout << "Entradas: r1 = " << r1 << " ohm, r2 = " << r2 << " ohm, r3 = " << r3 << " ohm\n";
    cout << setprecision(6) << "Numerador = (" << setprecision(3) << r1 << ")(" << r2 << ") + ("
         << r2 << ")(" << r3 << ") + (" << r3 << ")(" << r1 << ") = " << setprecision(6) << num << "\n";
    cout << setprecision(3);
    cout << "  ra = " << setprecision(6) << num << " / " << setprecision(3) << r1 << " = " << ra << " ohm\n";
    cout << "  rb = " << setprecision(6) << num << " / " << setprecision(3) << r2 << " = " << rb << " ohm\n";
    cout << "  rc = " << setprecision(6) << num << " / " << setprecision(3) << r3 << " = " << rc << " ohm\n";

    return {ra, rb, rc};
}

Tripla delta_a_y(double ra, double rb, double rc, const string& nombre_paso, bool redondear) {
    double den = ra + rb + rc;
    double r1 = redondear3((rb * rc) / den, redondear);
    double r2 = redondear3((rc * ra) / den, redondear);
    double r3 = redondear3((ra * rb) / den, redondear);

    cout << "\n--- " << nombre_paso << " (Delta -> Estrella Y) ---\n";
    cout << fixed << setprecision(3);
    cout << "Entradas: ra = " << ra << " ohm, rb = " << rb << " ohm, rc = " << rc << " ohm\n";
    cout << "Denominador = " << ra << " + " << rb << " + " << rc << " = " << den << "\n";
    cout << "  r1 = (" << rb << ")(" << rc << ") / " << den << " = " << r1 << " ohm\n";
    cout << "  r2 = (" << rc << ")(" << ra << ") / " << den << " = " << r2 << " ohm\n";
    cout << "  r3 = (" << ra << ")(" << rb << ") / " << den << " = " << r3 << " ohm\n";

    return {r1, r2, r3};
}

double paralelo(double rx, double ry, const string& etiqueta, const string& nombre_paso, bool redondear) {
    double req = redondear3((rx * ry) / (rx + ry), redondear);

    cout << "\n--- " << nombre_paso << " (Paralelo: " << etiqueta << ") ---\n";
    cout << fixed << setprecision(3);
    cout << "  " << etiqueta << " = (" << rx << " * " << ry << ") / (" << rx << " + " << ry << ") = "
         << setprecision(6) << (rx * ry) << " / " << setprecision(3) << (rx + ry) << " = " << req << " ohm\n";

    return req;
}

double serie(double rx, double ry, const string& etiqueta, const string& nombre_paso, bool redondear) {
    double req = redondear3(rx + ry, redondear);

    cout << "\n--- " << nombre_paso << " (Serie: " << etiqueta << ") ---\n";
    cout << fixed << setprecision(3);
    cout << "  " << etiqueta << " = " << rx << " + " << ry << " = " << req << " ohm\n";

    return req;
}

int main() {
    int opcion;
    char modo_redondeo;

    cout << "=================================================================\n";
    cout << "   RESOLUCION AUTOMATICA DE CIRCUITO COMPLEJO (C++ / CLion)      \n";
    cout << "=================================================================\n";
    cout << "1. Usar valores originales del ejercicio (V=48V, R=10,12,4...)\n";
    cout << "2. Ingresar nuevos valores manualmente\n";
    cout << "Selecciona una opcion (1 o 2): ";
    cin >> opcion;

    cout << "Redondear cada paso a 3 decimales como en la libreta? (s/n): ";
    cin >> modo_redondeo;
    bool redondear = (modo_redondeo != 'n' && modo_redondeo != 'N');

    double V;
    double R_AE, R_EF, R_EH, R_AH, R_HF, R_AD, R_DH, R_DC, R_FG, R_HG, R_HC, R_CG;

    if (opcion == 2) {
        cout << "\nVoltaje de la fuente V (en Volts): ";
        cin >> V;
        cout << "\nIngresa el valor de las 12 resistencias:\n";
        cout << "R(A-E) [original 10 ohm]: "; cin >> R_AE;
        cout << "R(E-F) [original 12 ohm]: "; cin >> R_EF;
        cout << "R(E-H) [original  4 ohm]: "; cin >> R_EH;
        cout << "R(A-H) [original  8 ohm]: "; cin >> R_AH;
        cout << "R(H-F) [original  9 ohm]: "; cin >> R_HF;
        cout << "R(A-D) [original  2 ohm]: "; cin >> R_AD;
        cout << "R(D-H) [original  7 ohm]: "; cin >> R_DH;
        cout << "R(D-C) [original 15 ohm]: "; cin >> R_DC;
        cout << "R(F-G) [original  5 ohm]: "; cin >> R_FG;
        cout << "R(H-G) [original  6 ohm]: "; cin >> R_HG;
        cout << "R(H-C) [original  3 ohm]: "; cin >> R_HC;
        cout << "R(C-G) [original 13 ohm]: "; cin >> R_CG;
    } else {
        V = 48.0;
        R_AE = 10.0; R_EF = 12.0; R_EH = 4.0;
        R_AH = 8.0;  R_HF = 9.0;  R_AD = 2.0;
        R_DH = 7.0;  R_DC = 15.0; R_FG = 5.0;
        R_HG = 6.0;  R_HC = 3.0;  R_CG = 13.0;
    }

    // Dibuja el circuito inicial con los valores cargados
    dibujar_circuito_inicial(V, R_AE, R_EF, R_EH, R_AH, R_HF, R_AD, R_DH, R_DC, R_FG, R_HG, R_HC, R_CG);

    cout << "\n================ INICIO DEL PROCEDIMIENTO ================\n";

    // PASO 1: Estrella en nodo H
    Tripla d1 = y_a_delta(R_AH, R_HC, R_HF, "PASO 1: Estrella en nodo H", redondear);

    // PASO 2: Estrella en nodo D
    Tripla d2 = y_a_delta(R_AD, R_DC, R_DH, "PASO 2: Estrella en nodo D", redondear);

    // PASO 3: Paralelo rq1
    double rq1 = paralelo(d1.c, d2.c, "rq1", "PASO 3", redondear);

    // PASO 4: Estrella en nodo E
    Tripla d3 = y_a_delta(R_AE, R_EF, R_EH, "PASO 4: Estrella en nodo E", redondear);

    // PASO 5: Paralelo rq2
    double rq2 = paralelo(d3.c, d1.b, "rq2", "PASO 5", redondear);

    // PASO 6: Paralelo rq3
    double rq3 = paralelo(d3.b, d2.b, "rq3", "PASO 6", redondear);

    // PASO 7: Delta izquierda -> Estrella
    Tripla y4 = delta_a_y(d2.a, rq3, rq1, "PASO 7: Delta izquierda", redondear);

    // PASO 8: Estrella central -> Delta
    Tripla d5 = y_a_delta(d3.a, R_HG, y4.c, "PASO 8: Estrella central", redondear);

    // PASO 9: Paralelo rq4
    double rq4 = paralelo(d5.c, R_FG, "rq4", "PASO 9", redondear);

    // PASO 10: Delta superior derecha -> Estrella
    Tripla y6 = delta_a_y(d5.a, d5.b, rq4, "PASO 10: Delta superior derecha", redondear);

    // PASO 11: Estrella superior -> Delta
    Tripla d7 = y_a_delta(rq2, d1.a, y6.a, "PASO 11: Estrella superior", redondear);

    // PASO 12: Estrella izquierda -> Delta
    Tripla d8 = y_a_delta(y4.a, y4.b, y6.c, "PASO 12: Estrella izquierda", redondear);

    // PASO 13: Paralelos rq5, rq6 y rq7
    double rq5 = paralelo(d7.b, d8.b, "rq5", "PASO 13a", redondear);
    double rq6 = paralelo(d7.a, d8.a, "rq6", "PASO 13b", redondear);
    double rq7 = paralelo(d7.c, d8.c, "rq7", "PASO 13c", redondear);

    // PASO 14: Estrella inferior derecha -> Delta
    Tripla d9 = y_a_delta(rq7, R_CG, rq6, "PASO 14: Estrella inferior derecha", redondear);

    // PASO 15: Paralelos rq8, rq9 y Serie
    double rq8 = paralelo(rq5, d9.b, "rq8", "PASO 15a", redondear);
    double rq9 = paralelo(y6.b, d9.a, "rq9", "PASO 15b", redondear);
    double r_serie = serie(rq8, rq9, "R_serie", "PASO 15c", redondear);

    // PASO 16: Paralelo final rq10 y Corriente Total Ix
    double rq10 = paralelo(d9.c, r_serie, "rq10 (R_total)", "PASO 16: Resistencia Total", redondear);
    double Ix = V / rq10;
    if (redondear) Ix = round(Ix * 10000.0) / 10000.0;

    // Dibuja el circuito equivalente final con los resultados
    dibujar_circuito_final(V, rq10, Ix);

    cout << "=================================================================\n";
    cout << "                      RESULTADOS FINALES                         \n";
    cout << "=================================================================\n";
    cout << fixed << setprecision(3);
    cout << "  Voltaje de la fuente (V)    : " << V << " V\n";
    cout << "  Resistencia Equivalente (Rq): " << rq10 << " ohm\n";
    cout << setprecision(4);
    cout << "  Corriente Total (Ix)        : " << Ix << " A\n";
    cout << "=================================================================\n";

    return 0;
}