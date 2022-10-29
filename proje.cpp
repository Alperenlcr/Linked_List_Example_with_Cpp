#include<iostream>
#include<stdio.h>
#include<cstring>
#include<fstream> 
#include<sstream>

using namespace std;

struct ogrenci
{
    char ogrno[15];
    char ad[30];
    char soyad[30];
    struct ders* dersdugumu;
    struct ogrenci* sonraki;
};

struct ders
{
    char derskodu[10];
    char dersadi[50];
    struct ders* sonraki;
};

int bul(struct ogrenci** root, char numara[30]);
struct ogrenci* kisi_ekle(struct ogrenci** root, char numara[30], char isim[30], char soyad[30],char derskodu[30], char dersadi[30]);
struct ogrenci* liste_kur(struct ogrenci** root);
struct ogrenci* ara(struct ogrenci* root,char key[30]);
struct ogrenci* ogrenciSil(struct ogrenci** root,char numara[30]);
struct ogrenci* dersSil(struct ogrenci** root, char numara[30],char kod[10]);
void print_List(struct ogrenci* root);
void kesisimBul(struct ogrenci* root,char kod_bir[10],char kod_iki[10]);
void dosyaya_yazma(struct ogrenci* root);

int main()
{
    struct ogrenci* root = nullptr;
    root = liste_kur(&root);
    struct ogrenci* deneme = root;

    char secim;
    bool cikis = true;
    char key[30], kod[30];
    while (cikis)
    {
        cout<<"\n\n\n\t***ISLEM MENUSU***\n";
        cout<<"Yapmak istediginiz islem icin asagidaki durumlardan birini giriniz.\n";
        cout<<"Arama yapma: A\nDers silme : D\nKesisim bulma : K\nListeyi ekrana yazdirma : L\n";
        cout<<"Ogrenci silme : O\nDosyaya yazma : Y\nCikis yapma : C\n\n";
        cin>>secim;
        switch (secim)
        {
        case 'A':
            cout<<"Arama yapmak icin ogrenci numarasi veya soyadi giriniz : ";
            cin>>key;
            deneme = ara(root, key);
            
            if (deneme == nullptr)
            {
                cout<<"\nBulunamadi";
                deneme = root;
            }
            else
            {
                if (atoi(root->ogrno) == atoi(deneme->ogrno))
                {
                    deneme = deneme;
                    struct ders* temp;
                    temp = deneme->dersdugumu;
                    cout<<endl;
                    cout << deneme->ogrno <<" ";
                    cout << deneme->ad    <<" ";
                    cout << deneme->soyad <<" ";
                    while (temp != nullptr)
                    {
                    cout << temp->dersadi <<" ";
                    cout << temp->derskodu<<" ";
                    temp = temp->sonraki;
                    }
                    deneme = root;
                }
                else
                {
                    deneme = deneme->sonraki;
                    struct ders* temp;
                    temp = deneme->dersdugumu;
                    cout<<endl;
                    cout << deneme->ogrno <<" ";
                    cout << deneme->ad    <<" ";
                    cout << deneme->soyad <<" ";
                    while (temp != nullptr)
                    {
                    cout << temp->dersadi <<" ";
                    cout << temp->derskodu<<" ";
                    temp = temp->sonraki;
                    }
                    deneme = root;
                }
            }
            
            break;
        case 'D':
            cout<<"Ders silmek icin ogrenci numarasi veya soyadi giriniz : ";
            cin>>key;
            cout<<"Ders kodu giriniz : ";
            cin>>kod;
            deneme = dersSil(&deneme,key,kod);
            
            if (deneme == nullptr)
            {
                cout<<"\nBulunamadi";
                deneme = root;
            }
            else
            {
                root = deneme;
                cout<<"Basari ile silindi.\n";
            }
            break;
        case 'K':
            cout<<"Kesisim icin ilk kodu giriniz : ";
            cin>>key;
            cout<<"Kesisim icin ikinci kodu giriniz : ";
            cin>>kod;
            kesisimBul(root, key, kod);
            break;
        case 'L':
            print_List(root);
            break;
        case 'O':
            cout<<"Ogrenci silmek icin ogrenci numarasi giriniz : ";
            cin>>key;
            deneme = ogrenciSil(&deneme,key);
            
            if (deneme == nullptr)
            {
                cout<<"\nBulunamadi";
                deneme = root;
            }
            else
            {
                root = deneme;
                cout<<"Basari ile silindi.\n";
            }

            break;
        case 'Y':
            dosyaya_yazma(root);
            cout<<"Basari ile dosya olusturuldu.\n";
            break;
        case 'C':
            cikis = false;
            break;
        default:
            cout<<"Yanlis secim yaptiniz tekrar deneyin !";
            break;
        }
    }
    return 0;
}

void dosyaya_yazma(struct ogrenci* root)
{
    ofstream myfile("ogrenciler.txt");
    int count;
    struct ogrenci* iter = root;
    struct ders* temp;
    string line;
    if ( ! myfile.is_open())
        cout<<"\ndosya acilamadi\n";

    while (iter != nullptr)
    {
        line = "";
        temp = iter->dersdugumu;
        count = 0;
        while (temp != nullptr)
        {
            if(count == 0)
            {
                line.append(iter->ogrno);
                line.append(" ");
                line.append(iter->ad);
                line.append(" ");
                line.append(iter->soyad);
                line.append(" ");
                count = 1;
            }
            line.append(temp->dersadi);
            line.append(" ");
            line.append(temp->derskodu);
            line.append(" ");
            temp = temp->sonraki;
        }
        line.append("\n");
        myfile << line;
        iter = iter->sonraki;
    }
    myfile.close();
}

int bul(struct ogrenci** root, char numara[30])
{
    struct ogrenci* current = *root;
    while (current != nullptr)
    {
        if (atoi(current->ogrno) == atoi(numara))
            return 1;
        current = current->sonraki;
    }
    return 0;
}

struct ogrenci* kisi_ekle(struct ogrenci** root, char numara[30], char isim[30], char soyad[30],char derskodu[30], char dersadi[30])
{
    //cout<<numara<<" "<<isim<<" "<<soyad<<" "<<derskodu<<" "<<dersadi<<endl;
    struct ogrenci* iter;

    // var mi varsa ders ekle
    if (bul(root, numara))
    {
        iter = *root;
        while (strcmp(iter->ogrno, numara)!=0)
            iter = iter->sonraki;
        struct ders* temp = iter->dersdugumu;
        while (temp->sonraki != nullptr)
        {
            temp = temp->sonraki;
        }
        temp->sonraki = new struct ders;
        strcpy(temp->sonraki->dersadi,dersadi);
        strcpy(temp->sonraki->derskodu,derskodu);
        temp->sonraki->sonraki = nullptr;
    }

    // yoksa yeni ogrenci olustur siraya sok
    else
    {
        struct ogrenci* yeni = new struct ogrenci;
        iter = *root;
        strcpy(yeni->ogrno, numara);
        strcpy(yeni->ad, isim);
        strcpy(yeni->soyad, soyad);
        yeni->sonraki = nullptr;
        
        yeni->dersdugumu = new struct ders;
        strcpy(yeni->dersdugumu->dersadi,dersadi);
        strcpy(yeni->dersdugumu->derskodu,derskodu);
        yeni->dersdugumu->sonraki = nullptr;

        // siraya sok
        if (iter == nullptr) // ilk ogrenci
        {
            *root = yeni;
        }
        else
        {
            while (iter->sonraki != nullptr && atoi(iter->sonraki->ogrno) < atoi(numara))
                iter = iter->sonraki;

            yeni->sonraki = iter->sonraki;
            iter->sonraki = yeni;
        }
    }
    return *root;
}

struct ogrenci* liste_kur(struct ogrenci** root)
{
    fstream okuma;
    string line, word;
    int i=0;
    char files[3][50] = {"mat101.txt","fiz101.txt","eng101.txt"};
    char derskodu[50], dersadi[50], isim[50], soyad[50], numara[50];

    for ( i = 0; i < 3; i++)
    {
        okuma.open(files[i]);

        getline(okuma, line);
        stringstream s(line);
        s>>derskodu;
        s>>dersadi;

        while (getline(okuma, line))
        {
            stringstream s(line);
            s>>numara;
            s>>isim;
            s>>soyad;
            *root = kisi_ekle(root, numara,isim, soyad, derskodu, dersadi);
            ogrenci** temp = root;
        }
        okuma.close();
    }
    return *root;
}

struct ogrenci* ara(struct ogrenci* root,char key[30])
{
    int i = 0;
    if (key[0] <= '9' && key[0] >= '0')
    {
        if (atoi(root->ogrno) == atoi(key))
            return root;
        
        while (root->sonraki != nullptr)
        {
            if (atoi(root->sonraki->ogrno) == atoi(key))
                return root;

            root = root->sonraki;
        }
    }
    else
    {
        for (i = 0; i < strlen(key);i++)
        {
            key[i] = toupper(key[i]);
            
        }
        while (root->sonraki != nullptr)
        {
            if (strcmp(root->sonraki->soyad,key) == 0)
                return root;
        
            root = root->sonraki;
        }
    }
    return nullptr;
}

struct ogrenci* ogrenciSil(struct ogrenci** root,char numara[30])
{
    struct ogrenci* control = ara(*root,numara) ;
    if (control != nullptr && control->sonraki != nullptr)
    {
        struct ogrenci* temp;
        //Ilk öğrenci ise
        if (atoi((*root)->ogrno) == atoi(numara) )
        {
            while ((*root)->dersdugumu != nullptr)
            {
                struct ders* gecici = (*root)->dersdugumu;
                (*root)->dersdugumu = (*root)->dersdugumu->sonraki;
                delete gecici;
            }
            temp = (*root);
            (*root) = (*root)->sonraki;
            delete temp;
            return *root;
        }
        else
        {
            while (control->sonraki->dersdugumu != nullptr)
            {
                struct ders* gecici = control->sonraki->dersdugumu;
                control->sonraki->dersdugumu = control->sonraki->dersdugumu->sonraki;
                delete gecici;
            }
            temp = control->sonraki;
            control->sonraki = control->sonraki->sonraki;
            delete temp;
            return *root;
        }
    }
    return nullptr;
}

struct ogrenci* dersSil(struct ogrenci** root, char numara[30],char kod[10])
{
    struct ogrenci* control = ara(*root,numara) ;
    if (control != nullptr && control->sonraki != nullptr)
    {
        struct ders* gecici;
        struct ders* iter;
        if (atoi((*root)->ogrno) == atoi(numara))
        {
            if (strcmp((*root)->dersdugumu->derskodu,kod) == 0)
            {
                gecici = (*root)->dersdugumu;
                (*root)->dersdugumu = (*root)->dersdugumu->sonraki;
                delete gecici;
                return ogrenciSil(root,numara);
            }
            else
            {
                iter = (*root)->dersdugumu;
                while (iter->sonraki != nullptr && strcmp(iter->sonraki->derskodu,kod) != 0)
                    iter = iter->sonraki;
                if (iter->sonraki == nullptr)
                    return nullptr;
                gecici = iter->sonraki;
                iter->sonraki = iter->sonraki->sonraki;
                delete gecici;
                return *root;
            }
        }
        
        if (strcmp(control->sonraki->dersdugumu->derskodu,kod) == 0)
        {
            gecici = control->sonraki->dersdugumu;
            control->sonraki->dersdugumu = control->sonraki->dersdugumu->sonraki;
            delete gecici;
            return ogrenciSil(root,numara);
        }
        else
        {
            iter = control->sonraki->dersdugumu;
            while (iter->sonraki != nullptr && strcmp(iter->sonraki->derskodu,kod) != 0)
                iter = iter->sonraki;
            if (iter->sonraki == nullptr)
                return nullptr;
            gecici = iter->sonraki;
            iter->sonraki = iter->sonraki->sonraki;
            delete gecici;
            return *root;
        }
    }
    return nullptr;
}
void print_List(struct ogrenci* root)
{
    int count;
    struct ogrenci* iter = root;
    struct ders* temp;
    while (iter != nullptr)
    {
        temp = iter->dersdugumu;
        count = 0;
        while (temp != nullptr)
        {
            if(count == 0)
            {
                cout<<endl;
                cout << iter->ogrno <<" ";
                cout << iter->ad    <<" ";
                cout << iter->soyad <<" ";
                count = 1;
            }
            cout << temp->dersadi <<" ";
            cout << temp->derskodu<<" ";
            temp = temp->sonraki;
        }
        iter = iter->sonraki;
    }
}
void kesisimBul(struct ogrenci* root,char kod_bir[10],char kod_iki[10])
{
    int count,check;
    struct ogrenci* iter = root;
    struct ders* temp;
    while (iter != nullptr)
    {
        temp = iter->dersdugumu;
        count = 0;
        check = 0;
        while (temp != nullptr)
        {
            if ((strcmp(temp->derskodu,kod_bir) == 0) || (strcmp(temp->derskodu,kod_iki) == 0))
                check++;
                
            if(check == 2 && count == 0)
            {
                cout<<endl;
                cout << iter->ogrno <<" ";
                cout << iter->ad    <<" ";
                cout << iter->soyad <<" ";
                count = 1;
            }
            temp = temp->sonraki;
        }
        iter = iter->sonraki;
    }
}