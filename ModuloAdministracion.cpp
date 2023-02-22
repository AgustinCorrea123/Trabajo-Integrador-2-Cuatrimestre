#include <stdio.h>
#include <stdlib.h>
#include "conio.c"
#include <string.h>
#include <ctype.h>

// ESTRUCTURAS

struct fecha
{
    int dia;
    int mes;
    int anio;
};

struct Dia
{
    char dias[6];
};

struct usuario
{
    char apeNom[60];
    char usuario[10];
    char contrasenia[10];
    char tipoUsuario;
    int dni;
};

struct Entrenador
{
    char apeNom[60];
    int legajoEntrenador;
    Dia diaAtencion[6];
    char contrasenia[10];
};

struct Socios
{
    char apeNom[60];
    char domicilio[60];
    int dni;
    int edad;
    fecha fechaDeIngreso;
    char indicacionMedica[100];
    float altura;
    float peso;
    int nroSocio;
    int actividades[6];
};

struct atenciones
{
    char apeNom[60];
    int cantAten;
    float porc;
};

struct actividad
{
    int key;
    char nomActividad[20];
    int hora;
    int legEntrador;
    int cantSocios;
    int nroSocios[50];
    char detalles[380];
};

// FUNCIONES
void menu(); //Menu principal
void registroUser(); //Registro de usuarios
void registroUserEntrenador();//Regsitro de entrenador
void regActividadesGym();//Registro de actividades del GYM
void calculoPagoEntrenador();//Calculo de pago por entrenador
void entrenadroMayCargaHoraria(); //Entrenador con Mayor horas
bool verificarPassword(usuario pass); //Funcion para cumplir condiciones de la contraseña
bool verifUser(usuario user); //Funcion para cumplir con las condiciones del usuario
int calCantAct(int legajo); //Funcion para calcaular la cantidad de actividades del entrenador

int main()
{
    menu();
    return 0;
}

void menu()
{
    bool band = true;
    int Op;
    const char *titulo = "Modulo de Administracion";
    const char *opciones[] = {"Registrar usuario de Recepcion", "Registrar Actividades del Gym", "Calcular pago al entreandor", "Entrenador con mayor carga horaria", "Salir"};
    do
    {
        system("cls");
        textcolor(RED);
		printf("\n\n\n\n\t\t\t\t--------|%s|--------\n\n\n", titulo);
		textcolor(WHITE);
        for (int i = 0; i < 5; i++)
        {
            printf("\t\t\t\t  %d. %s\n", i + 1, opciones[i]);
        }
        printf("\n\t\t\t\t  Ingrese una opcion: ");
        scanf("%d", &Op);
        switch (Op)
        {
        case 1:
            system("cls");
            registroUser();
            break;
        case 2:
            system("cls");
            regActividadesGym();
            break;
        case 3:
            system("cls");
            calculoPagoEntrenador();
            break;
        case 4:
            system("cls");
            entrenadroMayCargaHoraria();
            break;
        case 5:
            band = false;
            break;
        default:
            system("cls");
            textcolor(YELLOW);
            printf("\n\n\n\n\n\n\t\t\t\tError, respuesta invalida intente nuevamente...");
            textcolor(WHITE);
            system("pause>nul");
        }
    } while (band);
    system("cls");
    textcolor(BLUE);
    printf("\n\n\n\n\n\n\t\t\t\tSe cerro el modulo de ADMINISTRACION. Adios...\n\n\n\n");
    textcolor(WHITE);
    system("pause>nul");
}

void registroUser()
{
    usuario user;
    FILE *arch = fopen("Usuarios.dat", "a+b");
    usuario aux;
    char tipoUsuario;
    bool band = false, vBool;
    system("cls");
    textcolor(RED);
    printf("\n\n\t\t\t\t\t------|REGISTRO USUARIO|------\n\n");
    textcolor(WHITE);
    printf("\n\n\t\t\tINGRESE TIPO DE USUARIO [E=Entrenador / R=Recepcionista]: ");
    scanf("%s", &tipoUsuario);
    if (tipoUsuario == 'E' || tipoUsuario == 'e')
    {
        registroUserEntrenador();
    }
    else
    {
        do
        {
            band = false;
            system("cls");
            textcolor(RED);
    		printf("\n\n\n\t\t\t\t\t------|REGISTRO RECEPCIONISTA|------\n");
    		textcolor(WHITE);
            printf("\n\n\n\t\tINGRESE USUARIO: ");
            _flushall();
            gets(user.usuario);
            vBool = verifUser(user);
            if (vBool == true)
            {
                rewind(arch);
                fread(&aux, sizeof(usuario), 1, arch);
                for (int i = 0; !feof(arch); i++)
                {
                    if (strcmp(user.usuario, aux.usuario) == 0)
                    {
                        band = true;
                        break;
                    }
                    fread(&aux, sizeof(usuario), 1, arch);
                }
                if (band)
                {
                	textcolor(YELLOW);
                    printf("\n\t\t\tEL USUARIO INGRESADO YA EXISTE, VUELVA A INTENTAR.");
                    textcolor(WHITE);
                    system("pause>nul");
                }
            }
            else
                system("pause>nul");
        } while (band == true or vBool == false);
        _flushall();
        do
        {
            system("cls");
            textcolor(RED);
    		printf("\n\n\n\t\t\t\t\t------|REGISTRO RECEPCIONISTA|------\n");
    		textcolor(WHITE);
            printf("\n\n\n\t\tINGRESE USUARIO: %s\n", user.usuario);
            printf("\n\t\tINGRESE CONTRASE%cA: ", 165);
            gets(user.contrasenia);
            band = verificarPassword(user);
        } while (band == false);

        printf("\n\t\tINGRESE APELLIDO Y NOMBRE: ");
        gets(user.apeNom);
        fseek(arch, sizeof(usuario), SEEK_END);
        fwrite(&user, sizeof(usuario), 1, arch);
        fclose(arch);
        textcolor(GREEN);
        printf("\n\n\n\n\t\t\t\t\tSE HA REGISTRADO DE FORMA EXITOSA.");
        textcolor(WHITE);
        system("pause>nul");
    }
}

void registroUserEntrenador()
{
    Entrenador ent, aux;
    usuario user;
    bool band = true, bandpass = false, bandleg = false;

    FILE *arch = fopen("Entrenador.dat", "a+b");
    do
    {
    	system("cls");
    	textcolor(RED);
    	printf("\n\n\n\t\t\t\t\t------|REGISTRO ENTRENADOR|------\n");
    	textcolor(WHITE);
        printf("\n\n\t\t\tINGRESE APELLIDO Y NOMBRE: ");
        _flushall();
        gets(ent.apeNom);
        printf("\n\t\t\tINGRESE LEGAJO: ");
        scanf("%d", &ent.legajoEntrenador);
        if (ent.legajoEntrenador == 0)
        {
        	textcolor(YELLOW);
        	printf("\n\n\t\tLegajo ingresado invalido. Intente nuevamente..");
        	textcolor(WHITE);
            system("pause>nul");
        }else{
        	rewind(arch);
        	fread(&aux, sizeof(Entrenador), 1, arch);
        		for (int i = 0; !feof(arch); i++)
        		{
            		if (ent.legajoEntrenador == aux.legajoEntrenador)
            		{
                		bandleg = true;
                		break;
        			}
        			fread(&aux, sizeof(ent), 1, arch);
        		}
		}
        
        if (bandleg)
        {
        	textcolor(YELLOW);
            printf("\n\t\t\tEl Legajo del ENTRENADOR YA EXISTE. Intente nuevamente.");
            textcolor(WHITE);
            system("pause>nul");
            registroUserEntrenador();
        }
    } while (band=false);

    if (ent.legajoEntrenador!=0)
    {
        do
        {
            printf("\n\t\t\tINGRESE CONTRASE%cA: ", 165);
            _flushall();
            gets(user.contrasenia);
            bandpass = verificarPassword(user);
        } while (bandpass == false);
        strcpy(ent.contrasenia, user.contrasenia);
        fseek(arch, sizeof(Entrenador), SEEK_END);
        fwrite(&ent, sizeof(Entrenador), 1, arch);
        textcolor(GREEN);
        printf("\n\n\n\n\t\t\t\t\tSE HA REGISTRADO DE FORMA EXITOSA.");
        textcolor(WHITE);
        system("pause>nul");
    }
    fclose(arch);
}

bool verifUser(usuario user)
{
    int large, c = 0;
    large = strlen(user.usuario);
    if (large > 10 and large < 6)
    {
    	textcolor(YELLOW);
        printf("\n\t\t\tEl usuario debe tener entre 6 y 10 caracteres...\n");
        textcolor(WHITE);
        system("pause>nul");
        return false;
    }
    if (user.usuario[0] > 122 or user.usuario[0] < 97)
    {
    	textcolor(YELLOW);
        printf("\n\t\t\tEl usuario debe comenzar con una minuscula...\n");
        textcolor(WHITE);
        system("pause>nul");
        return false;
    }
    for (int i = 0; i < large; i++)
    {
        if (user.usuario[i] >= 65 and user.usuario[i] <= 90)
        {
            c++;
        }
        if (c >= 2)
            break;
    }
    if (c < 2)
    {
    	textcolor(YELLOW);
        printf("\n\t\t\tEl usuario debe tener como minimo dos mayusculas...\n");
        textcolor(WHITE);
        system("pause>nul");
        return false;
    }
    c = 0;
    for (int i = 0; i < large; i++)
    {
        if (user.usuario[i] >= 33 and user.usuario[i] <= 64)
        {
            c++;
        }
        if (c > 3)
        {
        	textcolor(YELLOW);
            printf("\n\t\t\tEl usuario debe tener como maximo 3 digitos...\n");
            textcolor(WHITE);
            system("pause>nul");
            return false;
        }
    }
    return true;
}

bool verificarPassword(usuario pass)
{
    int contMay = 0, contMin = 0, contNum = 0;
    char aux[2];
    if (strlen(pass.contrasenia) > 32 or strlen(pass.contrasenia) < 6)
    {
    	textcolor(YELLOW);
        printf("\n\t\t\tLa Contrase%ca debe tener entre 6 y 32 caracteres...\n", 164);
        textcolor(WHITE);
        system("pause>nul");
        return false;
    }
    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
        if (pass.contrasenia[i] >= 65 && pass.contrasenia[i] <= 90)
            contMay++;
        if (pass.contrasenia[i] >= 97 && pass.contrasenia[i] <= 122)
            contMin++;
        if (pass.contrasenia[i] >= 97 && pass.contrasenia[i] <= 122)
            contNum++;
    }
    if (contMay == 0 || contMin == 0 || contNum == 0)
    {
    	textcolor(YELLOW);
        printf("\n\t\tLa Contrase%ca debe tener al menos una letra mayuscula, una letra minuscula y un numero...\n", 164);
        textcolor(WHITE);
        system("pause>nul");
        return false;
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
        if (pass.contrasenia[i] >= 160 && pass.contrasenia[i] <= 163 || pass.contrasenia[i] == 130 || pass.contrasenia[i] == 181 || pass.contrasenia[i] == 144 ||
            pass.contrasenia[i] == 214 || pass.contrasenia[i] == 224 || pass.contrasenia[i] == 233)
        {
        	textcolor(YELLOW);
            printf("\n\t\tLa Contrase%ca No puede contener acentos. Solo caracteres alfanumericos...\n", 164);
            textcolor(WHITE);
            system("pause>nul");
            return false;
        }
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
        if (pass.contrasenia[i] == '.' or pass.contrasenia[i] == ',' or pass.contrasenia[i] == ';' or pass.contrasenia[i] == ' ')
        {
        	textcolor(YELLOW);
            printf("\n\t\tLa Contrase%ca NO debe contener ningun caracter de puntuacion y/o espacios, solo caracteres alfanumericos...\n", 164);
            textcolor(WHITE);
			system("pause>nul");
            return false;
        }
    }

    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
        if (pass.contrasenia[i + 2] != '\0')
        {
            if (pass.contrasenia[i] <= 48 && pass.contrasenia[i] <= 57)
            {
                if (pass.contrasenia[i + 1] <= 48 && pass.contrasenia[i + 1] <= 57)
                {
                    if (pass.contrasenia[i + 2] <= 48 && pass.contrasenia[i + 2] <= 57)
                    {
                    	textcolor(YELLOW);
                        printf("\n\t\t\tLa Contrase%ca no debe tener 3 caracteres numericos consecutivos...\n", 164);
                        textcolor(WHITE);
                        system("pause>nul");
                        return false;
                    }
                }
            }
        }
    }
    for (int i = 0; i < strlen(pass.contrasenia); i++)
    {
        if (pass.contrasenia[i + 1] != '\0')
        {
            aux[0] = pass.contrasenia[i];
            aux[1] = pass.contrasenia[i + 1];
            toupper(aux[0]);
            toupper(aux[1]);
            if (aux[0] >= 65 && aux[0] <= 90 && aux[1] >= 65 && aux[1] <= 90)
            {
                if (aux[0] + 1 == aux[1])
                {
                	textcolor(YELLOW);
                    printf("\n\t\tLa Contrase%ca NO debe contener caracteres consecutivos que refieran a letras alfabeticamente consecutivas...\n", 164);
                    textcolor(WHITE);
					system("pause>nul");
                    return false;
                }
            }
        }
    }
    return true;
}

void regActividadesGym()
{

    FILE *arch = fopen("Actividades.dat", "a+b");
    actividad act, aux, x;
    int op;
    bool val = false;

    rewind(arch);
    if (feof(arch))
    {
        aux.key = 1;
    }
    else
    {
        while (!feof(arch))
        {
            fread(&x, sizeof(actividad), 1, arch);
        };
        aux.key = x.key + 1;
    };

    system("CLS");
    textcolor(RED);
	printf("\n\n\n\t\t\t\t\t--- | Registro de Actividad | ---\n");
   	textcolor(WHITE);

    printf("\n\t\tIngresa nombre de actividad ('Spining', 'Pilate','Zumba'): ");
    _flushall();
    gets(aux.nomActividad);
    printf("\n\t\tIngresa hora (formato 24 horas, solo horas): ");
    scanf("%d", &aux.hora);
    printf("\n\t\tIngresa legajo de Entrenador: ");
    scanf("%d", &aux.legEntrador);
    aux.cantSocios = 0;
    for (int i = 0; i < 50; i++)
    {
        aux.nroSocios[i] = 0;
    }
    fseek(arch, sizeof(actividad), SEEK_END);
    fwrite(&aux, sizeof(actividad), 1, arch);
    fclose(arch);
}

void calculoPagoEntrenador()
{

    float valor;
    int cantPersonas;
    int legajo;
    float pago;
	
	textcolor(RED);
    printf("\n\n\n\t\t\t\t\t--- | Calcular Pago de Entrenador | ---\n\n");
    textcolor(WHITE);
    printf("\n\t\tIngrese valor unitario: $ ");
    scanf("%f", &valor);
    printf("\n\t\tIngrese legajo del Entrenador: ");
    scanf("%d", &legajo);

    pago = float(valor * calCantAct(legajo));
	
	textcolor(GREEN);
    printf("\n\n\n\t\t\t\t\tEl pago del entrenador es: $ %.2f", pago);
    textcolor(WHITE);
    system("pause>nul");
}

//Calcula la cantidad de socios que tiene el entrenador y la devuelve en la funcion calculoPagoEntrenador();
int calCantAct(int legajo)
{
    FILE *arch1 = fopen("Actividades.dat", "a+b");
    actividad aux;
    int cont = 0;

    rewind(arch1);
    fread(&aux, sizeof(actividad), 1, arch1);
    while (!feof(arch1))
    {
        if (aux.legEntrador == legajo)
        {
            cont += aux.cantSocios;
        }
        fread(&aux, sizeof(actividad), 1, arch1);
    }
    fclose(arch1);
    return cont;
}

void entrenadroMayCargaHoraria()
{
    FILE *arch = fopen("Entrenador.dat", "r+b");
    FILE *arch1 = fopen("Actividades.dat", "r+b");
    Entrenador ent, entfinal;
    actividad act;
    int cantFinal = 0, aux = 0;

    rewind(arch);
    fread(&ent, sizeof(Entrenador), 1, arch);
    while (!feof(arch))
    {
        aux = 0;
        rewind(arch1);
        fread(&act, sizeof(actividad), 1, arch1);
        while (!feof(arch1))
        {
            if (ent.legajoEntrenador == act.legEntrador)
            {
                aux++;
            }

            fread(&act, sizeof(actividad), 1, arch1);
        }
        if (aux > cantFinal)
        {
            entfinal = ent;
            cantFinal = aux;
        }
        fread(&ent, sizeof(Entrenador), 1, arch);
    }
    textcolor(RED);
	printf("\n\n\n\t\t\t\t------|EL ENTRENADOR CON MAS CARGA HORARIA|------\n\n\n");
	textcolor(WHITE);
    printf("\n\t\t\t\t\tNOMBRE: %s - LEGAJO: %d", entfinal.apeNom, entfinal.legajoEntrenador);
    system("pause>nul");
}
