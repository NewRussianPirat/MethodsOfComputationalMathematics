//
// Created by Роман Алексеев on 01.10.2023.
//

#include <fstream>
#include <iostream>
#include "Double.h"
#include "Eigenvalues.h"
#include "FunctionApproximation.h"
#include "Matrix.h"
#include "Polynomial.h"
#include "Rational.h"
#include "SolveNonlinearEquation.h"
#include "SolveSystem.h"

int main(int argc, char **argv) {
    Double::setDecimal(16);
    std::cout.precision(5);
    double a = -3;  // Установка левой границы
    double b = 3;   // Установка правой границы
    std::vector<Double> points(101);
    for (int i = 0; i < 101; ++i) {
        points[i] = a + i * (b - a) / 100;  // Составление узлов для графиков
    }
    std::vector<Double> funcValues(101);
    //Задание первой функции e^cos(x)
    std::function<Double(Double)> f1 = [](const Double &x) -> Double { return Double::exp(Double::cos(x)); };
    for (int i = 0; i < 101; ++i) {
        funcValues[i] = f1(points[i]);  // Поиск значений функции в найденых ранее точках
    }
    // Поиск интерполяционных многочленов
    Polynomial<Double> C13 = FunctionApproximation::newtonApproximation(3, a, b, f1);
    Polynomial<Double> C110 = FunctionApproximation::newtonApproximation(10, a, b, f1);
    Polynomial<Double> C120 = FunctionApproximation::newtonApproximation(20, a, b, f1);
    Polynomial<Double> P13 = FunctionApproximation::equidistantNewtonApproximation(3, a, b, f1);
    Polynomial<Double> P110 = FunctionApproximation::equidistantNewtonApproximation(10, a, b, f1);
    Polynomial<Double> P120 = FunctionApproximation::equidistantNewtonApproximation(20, a, b, f1);
    // Поиск интерполяционных многочленов в начале и конце таблицы
    Polynomial<Double> P13TB = FunctionApproximation::equidistantNewtonApproximation(3, a, b, f1, 1);
    Polynomial<Double> P110TB = FunctionApproximation::equidistantNewtonApproximation(10, a, b, f1, 1);
    Polynomial<Double> P120TB = FunctionApproximation::equidistantNewtonApproximation(20, a, b, f1, 1);
    Polynomial<Double> P13TE = FunctionApproximation::equidistantNewtonApproximation(3, a, b, f1, 2);
    Polynomial<Double> P110TE = FunctionApproximation::equidistantNewtonApproximation(10, a, b, f1, 2);
    Polynomial<Double> P120TE = FunctionApproximation::equidistantNewtonApproximation(20, a, b, f1, 2);

    //Задание второй функции abs(abs(x)-1)
    std::function<Double(Double)> f2 = [](const Double &x) -> Double { return Double::abs(Double::abs(x) - 1); };
    for (int i = 0; i < 101; ++i) {
        funcValues[i] = f1(points[i]);  // Поиск значений функции в найденых ранее точках
    }
    // Поиск интерполяционных многочленов
    Polynomial<Double> C23 = FunctionApproximation::newtonApproximation(3, a, b, f2);
    Polynomial<Double> C210 = FunctionApproximation::newtonApproximation(10, a, b, f2);
    Polynomial<Double> C220 = FunctionApproximation::newtonApproximation(20, a, b, f2);
    Polynomial<Double> P23 = FunctionApproximation::equidistantNewtonApproximation(3, a, b, f2);
    Polynomial<Double> P210 = FunctionApproximation::equidistantNewtonApproximation(10, a, b, f2);
    Polynomial<Double> P220 = FunctionApproximation::equidistantNewtonApproximation(20, a, b, f2);
    // Поиск интерполяционных многочленов в начале и конце таблицы
    Polynomial<Double> P23TB = FunctionApproximation::equidistantNewtonApproximation(3, a, b, f2, 1);
    Polynomial<Double> P210TB = FunctionApproximation::equidistantNewtonApproximation(10, a, b, f2, 1);
    Polynomial<Double> P220TB = FunctionApproximation::equidistantNewtonApproximation(20, a, b, f2, 1);
    Polynomial<Double> P23TE = FunctionApproximation::equidistantNewtonApproximation(3, a, b, f2, 2);
    Polynomial<Double> P210TE = FunctionApproximation::equidistantNewtonApproximation(10, a, b, f2, 2);
    Polynomial<Double> P220TE = FunctionApproximation::equidistantNewtonApproximation(20, a, b, f2, 2);

    //--------------------- Вывод результатов -------------------------------

    double h1 = 2;
    double h2 = 0.6;    //Укажите свои шаги
    double h3 = 0.3;
    std::cout << "P13: " << P13 << std::endl << "\nP110: " << P110 << std::endl << "\nP120: " << P120 << std::endl;
    std::cout << "\nC13: " << C13 << std::endl << "\nC110: " << C110 << std::endl << "\nC120: " << C120 << std::endl;
    std::cout
            << "\n n | max{|P1n(xi)-f1(xi)|} | max{|C1n(xi)-f1(xi)|} |\n";
    for (int i = 0; i < 3; ++i) {
        Polynomial<Double> *P;
        Polynomial<Double> *C;
        double h = 0;
        int n = 0;
        switch (i) {
            case 0: {
                P = &P13;
                C = &C13;
                h = h1;
                n = 3;
                break;
            }
            case 1: {
                P = &P110;
                C = &C110;
                h = h2;
                n = 10;
                break;
            }
            case 2: {
                P = &P120;
                C = &C120;
                h = h3;
                n = 20;
                break;
            }
            default:
                break;
        }
        Double maxP = 0;
        Double maxC = 0;
        for (int j = 0; j < 101; ++j) {
            Double p = Double::abs(P->solve(points[j]) - f1(points[j]));
            if (p > maxP) {
                maxP = p;
            }
            Double c = Double::abs(C->solve(points[j]) - f1(points[j]));
            if (c > maxC) {
                maxC = c;
            }
        }
        std::cout << std::setw(3) << n << "|" << std::setw(23) << maxP << "|" << std::setw(23) << maxC << "|\n";
    }
    std::cout << "\nP23: " << P23 << std::endl << "\nP210: " << P210 << std::endl << "\nP220: " << P220 << std::endl;
    std::cout << "\nC23: " << C23 << std::endl << "\nC210: " << C210 << std::endl << "\nC220: " << C220 << std::endl;
    std::cout << "\n n | max{|P2n(xi)-f2(xi)|} | max{|C2n(xi)-f2(xi)|} |\n";
    for (int i = 0; i < 3; ++i) {
        Polynomial<Double> *P;
        Polynomial<Double> *C;
        double h = 0;
        int n = 0;
        switch (i) {
            case 0: {
                P = &P23;
                C = &C23;
                h = h1;
                n = 3;
                break;
            }
            case 1: {
                P = &P210;
                C = &C210;
                h = h2;
                n = 10;
                break;
            }
            case 2: {
                P = &P220;
                C = &C220;
                h = h3;
                n = 20;
                break;
            }
            default:
                break;
        }
        Double maxP = 0;
        Double maxC = 0;
        for (int j = 0; j < 101; ++j) {
            Double t = (points[j] - a) / h;
            Double p = Double::abs(P->solve(points[j]) - f2(points[j]));
            if (p > maxP) {
                maxP = p;
            }
            Double c = Double::abs(C->solve(points[j]) - f2(points[j]));
            if (c > maxC) {
                maxC = c;
            }
        }
        std::cout << std::setw(3) << n << "|" << std::setw(23) << maxP << "|" << std::setw(23) << maxC << "|\n";
    }
    std::cout << std::endl;

    //-------------------------- Wolfram ------------------------------
    //----------- Далее будет указано, где что поменять ---------------

    std::ofstream out1("../../src/out1.txt");
    if (out1.is_open()) {
        out1 << "pointsC13 = {";
        for (int i = 0; i < 101; ++i) {
            out1 << "{" << points[i] << "," << C13.solve(points[i]) << "}";
            if (i != 100) {
                out1 << ",";
            }
        }
        out1 << "};\npointsC110 = {";
        for (int i = 0; i < 101; ++i) {
            out1 << "{" << points[i] << "," << C110.solve(points[i]) << "}";
            if (i != 100) {
                out1 << ",";
            }
        }
        out1 << "};\npointsC120 = {";
        for (int i = 0; i < 101; ++i) {
            out1 << "{" << points[i] << "," << C120.solve(points[i]) << "}";
            if (i != 100) {
                out1 << ",";
            }
        }
        out1 << "};\npointsP13 = {";
        for (int i = 0; i < 101; ++i) {
            out1 << "{" << points[i] << "," << P13.solve(points[i]) << "}";
            if (i != 100) {
                out1 << ",";
            }
        }
        out1 << "};\npointsP110 = {";
        for (int i = 0; i < 101; ++i) {
            out1 << "{" << points[i] << "," << P110.solve(points[i]) << "}";
            if (i != 100) {
                out1 << ",";
            }
        }
        out1 << "};\npointsP120 = {";
        for (int i = 0; i < 101; ++i) {
            out1 << "{" << points[i] << "," << P120.solve(points[i]) << "}";
            if (i != 100) {
                out1 << ",";
            }
        }
        out1 << "};\n";

        //--------------------- Изменить первые две строки (вписать свою первую функцию) ----------------------

        out1 << "f1 = Plot[E^Cos[x], {x, -3, 3}, PlotStyle -> {Blue, Thickness[0.007]},\n"
                "    PlotLegends -> Placed[Style[\"E^Cos[x]\", Blue], Below]];\n"
                "Show[f1, \n"
                " ListPlot[pointsP13, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP13, PlotStyle -> Red], \n"
                " ListPlot[pointsC13, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC13, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP110, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP110, PlotStyle -> Red], \n"
                " ListPlot[pointsC110, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC110, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP120, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP120, PlotStyle -> Red], \n"
                " ListPlot[pointsC120, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC120, PlotStyle -> Green]]";
        out1.close();
    }

    std::ofstream out2("../../src/out2.txt");
    if (out2.is_open()) {
        out2 << "pointsC23 = {";
        for (int i = 0; i < 101; ++i) {
            out2 << "{" << points[i] << "," << C23.solve(points[i]) << "}";
            if (i != 100) {
                out2 << ",";
            }
        }
        out2 << "};\npointsC210 = {";
        for (int i = 0; i < 101; ++i) {
            out2 << "{" << points[i] << "," << C210.solve(points[i]) << "}";
            if (i != 100) {
                out2 << ",";
            }
        }
        out2 << "};\npointsC220 = {";
        for (int i = 0; i < 101; ++i) {
            out2 << "{" << points[i] << "," << C220.solve(points[i]) << "}";
            if (i != 100) {
                out2 << ",";
            }
        }
        out2 << "};\npointsP23 = {";
        for (int i = 0; i < 101; ++i) {
            out2 << "{" << points[i] << "," << P23.solve(points[i]) << "}";
            if (i != 100) {
                out2 << ",";
            }
        }
        out2 << "};\npointsP210 = {";
        for (int i = 0; i < 101; ++i) {
            out2 << "{" << points[i] << "," << P210.solve(points[i]) << "}";
            if (i != 100) {
                out2 << ",";
            }
        }
        out2 << "};\npointsP220 = {";
        for (int i = 0; i < 101; ++i) {
            out2 << "{" << points[i] << "," << P220.solve(points[i]) << "}";
            if (i != 100) {
                out2 << ",";
            }
        }
        out2 << "};\n";

        //--------------------- Изменить первую и третью строки (вписать свою вторую функцию) ----------------------

        out2 << "f2 = Plot[Abs[Abs[x] - 1], {x, -3, 3}, \n"
                "   PlotStyle -> {Blue, Thickness[0.007]}, \n"
                "   PlotLegends -> Placed[Style[\"Abs[Abs[x] - 1]\", Blue], Below]];\n"
                "Show[\n"
                " f2,\n"
                " ListPlot[pointsP23, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(2, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]],\n"
                " ListLinePlot[pointsP23, PlotStyle -> Red],\n"
                " ListPlot[pointsC23, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(2, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]],\n"
                " ListLinePlot[pointsC23, PlotStyle -> Green]\n"
                " ]\n"
                "Show[\n"
                " f2,\n"
                " ListPlot[pointsP210, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(2, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]],\n"
                " ListLinePlot[pointsP210, PlotStyle -> Red],\n"
                " ListPlot[pointsC210, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(2, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]],\n"
                " ListLinePlot[pointsC210, PlotStyle -> Green]\n"
                " ]\n"
                "Show[\n"
                " f2,\n"
                " ListPlot[pointsP220, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(2, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]],\n"
                " ListLinePlot[pointsP220, PlotStyle -> Red],\n"
                " ListPlot[pointsC220, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(2, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]],\n"
                " ListLinePlot[pointsC220, PlotStyle -> Green]\n"
                " ]";

        out2.close();
    }

    std::ofstream out3("../../src/out3.txt");
    if (out3.is_open()) {
        out3 << "pointsC13 = {";
        for (int i = 0; i < 101; ++i) {
            out3 << "{" << points[i] << "," << C13.solve(points[i]) << "}";
            if (i != 100) {
                out3 << ",";
            }
        }
        out3 << "};\npointsC110 = {";
        for (int i = 0; i < 101; ++i) {
            out3 << "{" << points[i] << "," << C110.solve(points[i]) << "}";
            if (i != 100) {
                out3 << ",";
            }
        }
        out3 << "};\npointsC120 = {";
        for (int i = 0; i < 101; ++i) {
            out3 << "{" << points[i] << "," << C120.solve(points[i]) << "}";
            if (i != 100) {
                out3 << ",";
            }
        }
        out3 << "};\npointsP13TB = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - a) / h1;
            out3 << "{" << points[i] << "," << P13TB.solve(t) << "}";
            if (i != 100) {
                out3 << ",";
            }
        }
        out3 << "};\npointsP110TB = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - a) / h2;
            out3 << "{" << points[i] << "," << P110TB.solve(t) << "}";
            if (i != 100) {
                out3 << ",";
            }
        }
        out3 << "};\npointsP120TB = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - a) / h3;
            out3 << "{" << points[i] << "," << P120TB.solve(t) << "}";
            if (i != 100) {
                out3 << ",";
            }
        }
        out3 << "};\n";

        //--------------------- Изменить первые две строки (вписать свою первую функцию) ----------------------

        out3 << "f1 = Plot[E^Cos[x], {x, -3, 3}, PlotStyle -> {Blue, Thickness[0.007]},\n"
                "    PlotLegends -> Placed[Style[\"E^Cos[x]\", Blue], Below]];\n"
                "Show[f1, \n"
                " ListPlot[pointsP13TB, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP13TB, PlotStyle -> Red], \n"
                " ListPlot[pointsC13, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC13, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP110TB, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP110TB, PlotStyle -> Red], \n"
                " ListPlot[pointsC110, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC110, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP120TB, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP120TB, PlotStyle -> Red], \n"
                " ListPlot[pointsC120, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC120, PlotStyle -> Green]]";
        out3.close();
    }

    std::ofstream out4("../../src/out4.txt");
    if (out4.is_open()) {
        out4 << "pointsC13 = {";
        for (int i = 0; i < 101; ++i) {
            out4 << "{" << points[i] << "," << C13.solve(points[i]) << "}";
            if (i != 100) {
                out4 << ",";
            }
        }
        out4 << "};\npointsC110 = {";
        for (int i = 0; i < 101; ++i) {
            out4 << "{" << points[i] << "," << C110.solve(points[i]) << "}";
            if (i != 100) {
                out4 << ",";
            }
        }
        out4 << "};\npointsC120 = {";
        for (int i = 0; i < 101; ++i) {
            out4 << "{" << points[i] << "," << C120.solve(points[i]) << "}";
            if (i != 100) {
                out4 << ",";
            }
        }
        out4 << "};\npointsP13TE = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - b) / h1;
            out4 << "{" << points[i] << "," << P13TE.solve(t) << "}";
            if (i != 100) {
                out4 << ",";
            }
        }
        out4 << "};\npointsP110TE = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - b) / h2;
            out4 << "{" << points[i] << "," << P110TE.solve(t) << "}";
            if (i != 100) {
                out4 << ",";
            }
        }
        out4 << "};\npointsP120TE = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - b) / h3;
            out4 << "{" << points[i] << "," << P120TE.solve(t) << "}";
            if (i != 100) {
                out4 << ",";
            }
        }
        out4 << "};\n";

        //--------------------- Изменить первые две строки (вписать свою первую функцию) ----------------------

        out4 << "f1 = Plot[E^Cos[x], {x, -3, 3}, PlotStyle -> {Blue, Thickness[0.007]},\n"
                "    PlotLegends -> Placed[Style[\"E^Cos[x]\", Blue], Below]];\n"
                "Show[f1, \n"
                " ListPlot[pointsP13TE, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP13TE, PlotStyle -> Red], \n"
                " ListPlot[pointsC13, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC13, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP110TE, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP110TE, PlotStyle -> Red], \n"
                " ListPlot[pointsC110, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC110, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP120TE, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP120TE, PlotStyle -> Red], \n"
                " ListPlot[pointsC120, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC120, PlotStyle -> Green]]";
        out4.close();
    }

    std::ofstream out5("../../src/out5.txt");
    if (out5.is_open()) {
        out5 << "pointsC23 = {";
        for (int i = 0; i < 101; ++i) {
            out5 << "{" << points[i] << "," << C23.solve(points[i]) << "}";
            if (i != 100) {
                out5 << ",";
            }
        }
        out5 << "};\npointsC210 = {";
        for (int i = 0; i < 101; ++i) {
            out5 << "{" << points[i] << "," << C210.solve(points[i]) << "}";
            if (i != 100) {
                out5 << ",";
            }
        }
        out5 << "};\npointsC220 = {";
        for (int i = 0; i < 101; ++i) {
            out5 << "{" << points[i] << "," << C220.solve(points[i]) << "}";
            if (i != 100) {
                out5 << ",";
            }
        }
        out5 << "};\npointsP23TB = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - a) / h1;
            out5 << "{" << points[i] << "," << P23TB.solve(t) << "}";
            if (i != 100) {
                out5 << ",";
            }
        }
        out5 << "};\npointsP210TB = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - a) / h2;
            out5 << "{" << points[i] << "," << P210TB.solve(t) << "}";
            if (i != 100) {
                out5 << ",";
            }
        }
        out5 << "};\npointsP220TB = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - a) / h3;
            out5 << "{" << points[i] << "," << P220TB.solve(t) << "}";
            if (i != 100) {
                out5 << ",";
            }
        }
        out5 << "};\n";

        //--------------------- Изменить первые две строки (вписать свою первую функцию) ----------------------

        out5 << "f1 = Plot[Abs[Abs[x] - 1], {x, -3, 3}, PlotStyle -> {Blue, Thickness[0.007]},\n"
                "    PlotLegends -> Placed[Style[\"Abs[Abs[x] - 1]\", Blue], Below]];\n"
                "Show[f1, \n"
                " ListPlot[pointsP23TB, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP23TB, PlotStyle -> Red], \n"
                " ListPlot[pointsC23, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC23, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP210TB, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP210TB, PlotStyle -> Red], \n"
                " ListPlot[pointsC210, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC210, PlotStyle -> Green]]\n"
                "Show[f1, \n"
                " ListPlot[pointsP220TB, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]], ListLinePlot[pointsP220TB, PlotStyle -> Red], \n"
                " ListPlot[pointsC220, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(1, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]], ListLinePlot[pointsC220, PlotStyle -> Green]]";
        out5.close();
    }

    std::ofstream out6("../../src/out6.txt");
    if (out6.is_open()) {
        out6 << "pointsC23 = {";
        for (int i = 0; i < 101; ++i) {
            out6 << "{" << points[i] << "," << C23.solve(points[i]) << "}";
            if (i != 100) {
                out6 << ",";
            }
        }
        out6 << "};\npointsC210 = {";
        for (int i = 0; i < 101; ++i) {
            out6 << "{" << points[i] << "," << C210.solve(points[i]) << "}";
            if (i != 100) {
                out6 << ",";
            }
        }
        out6 << "};\npointsC220 = {";
        for (int i = 0; i < 101; ++i) {
            out6 << "{" << points[i] << "," << C220.solve(points[i]) << "}";
            if (i != 100) {
                out6 << ",";
            }
        }
        out6 << "};\npointsP23TE = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - b) / h1;
            out6 << "{" << points[i] << "," << P23TE.solve(t) << "}";
            if (i != 100) {
                out6 << ",";
            }
        }
        out6 << "};\npointsP210TE = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - b) / h2;
            out6 << "{" << points[i] << "," << P210TE.solve(t) << "}";
            if (i != 100) {
                out6 << ",";
            }
        }
        out6 << "};\npointsP220TE = {";
        for (int i = 0; i < 101; ++i) {
            Double t = (points[i] - b) / h3;
            out6 << "{" << points[i] << "," << P220TE.solve(t) << "}";
            if (i != 100) {
                out6 << ",";
            }
        }
        out6 << "};\n";

        //--------------------- Изменить первую и третью строки (вписать свою первую функцию) ----------------------

        out6 << "f2 = Plot[Abs[Abs[x] - 1], {x, -3, 3}, \n"
                "   PlotStyle -> {Blue, Thickness[0.007]}, \n"
                "   PlotLegends -> Placed[Style[\"Abs[Abs[x] - 1]\", Blue], Below]];\n"
                "Show[\n"
                " f2,\n"
                " ListPlot[pointsP23TE, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(2, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]],\n"
                " ListLinePlot[pointsP23TE, PlotStyle -> Red],\n"
                " ListPlot[pointsC23, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(2, \\\n"
                "3\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]],\n"
                " ListLinePlot[pointsC23, PlotStyle -> Green]\n"
                " ]\n"
                "Show[\n"
                " f2,\n"
                " ListPlot[pointsP210TE, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(2, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]],\n"
                " ListLinePlot[pointsP210TE, PlotStyle -> Red],\n"
                " ListPlot[pointsC210, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(2, \\\n"
                "10\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]],\n"
                " ListLinePlot[pointsC210, PlotStyle -> Green]\n"
                " ]\n"
                "Show[\n"
                " f2,\n"
                " ListPlot[pointsP220TE, PlotStyle -> {Red, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(P\\), \\(2, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Red], Below]],\n"
                " ListLinePlot[pointsP220TE, PlotStyle -> Red],\n"
                " ListPlot[pointsC220, PlotStyle -> {Green, PointSize[0.006]}, \n"
                "  PlotLegends -> \n"
                "   Placed[Style[\n"
                "     \"\\!\\(\\*SubscriptBox[\\(C\\), \\(2, \\\n"
                "20\\)]\\)(\\!\\(\\*OverscriptBox[SubscriptBox[\\(x\\), \\(i\\)], \\(_\\)]\\))\", \n"
                "     Green], Below]],\n"
                " ListLinePlot[pointsC220, PlotStyle -> Green]\n"
                " ]";
        out6.close();
    }

    return 0;
}
