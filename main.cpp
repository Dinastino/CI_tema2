#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

struct ColorConsole {
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox {
    void new_text() {/*...*/}
    void set_text(const string &text) {
        cout << text << endl;
    }
};

ConsoleBox *consoleBox = new ConsoleBox;

void load_script(const char* filename, bool show_script = false) {
    string script;
    FILE* f = nullptr;

    try {
        f = fopen(filename, "rb");
        if (!f) {
            cerr << "Error al abrir: " << filename << "\nFile no existe o  no es encontrada." << endl;
            return;
        }

        int c;
        char buf[4001];
        while ((c = fread(buf, 1, 4000, f)) > 0) {
            buf[c] = 0;
            script.append(buf);
        }

        if (ferror(f)) {
            cerr << "Error al leer archivo: " << filename << endl;
            return;
        }

        fclose(f);
        f = nullptr;

        if (show_script) {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white;
            cout << script << endl;
        }

        consoleBox->new_text();
        consoleBox->set_text(script);
    }
    catch (...) {
        cerr << "Error durante lectura del archivo." << endl;
        if (f) {
            fclose(f);
        }
    }
}

void load_script() {
    char filename[500];
    printf("Archivo: \n");
    scanf("%499s", filename);
    load_script(filename, true);
}

int main() {
    load_script();
    return 0;
}