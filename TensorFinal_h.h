#ifndef TENSORFINAL_H_H_INCLUDED
#define TENSORFINAL_H_H_INCLUDED


#include <iostream>
#include <vector>

using namespace std;

class Tensor{
public:
    Tensor(int x);
    Tensor(int x, int y);
    Tensor(int x, int y, int z);
    int getElem(int x);
    int getElem(int x, int y);
    int getElem(int x, int y, int z);
    void putElem(int coord, int value);
    void putElem(vector<int> coords, int x );
    Tensor cut(vector<int> cutShape);

    Tensor cut(vector<int> rows, vector<int> columns);
    Tensor cut(vector<int> x, vector<int> y, vector<int> z);

    void reshape(int x, int y);
    void reshape(int x, int y, int z);
    Tensor operator+(Tensor a);
    Tensor operator-(Tensor a);
    int* tensorAArray;
    int** tensorBArray;
    int*** tensorCArray;
    int x_t, y_t, z_t;
};



Tensor::Tensor(int x){
        x_t = x;
        tensorAArray = new int[x];
        for(int i = 0; i < x; i++){
            tensorAArray[i] = 0;
        }
    }
//перевизначенн конструктору для 2-виірного масиву
Tensor::Tensor(int x, int y){
        x_t = x;
        y_t = y;
        tensorBArray = new int* [x];
        for(int i = 0; i < x; i++){
            tensorBArray[i] = new int[y];
            for(int j = 0; j < y; j++){
                tensorBArray[i][j] = 0;
            }
        }
    }
//перевизначенн конструктору для 3-виірного масиву
Tensor::Tensor(int x, int y, int z){
        x_t = x;
        y_t = y;
        z_t = z;
        tensorCArray = new int**[x];
        for(int i = 0; i < x; i++){
            tensorCArray[i] = new int* [y];
            for(int j = 0; j < y; j++){
                tensorCArray[i][j] = new int[z];
                for(int k = 0; k < z; k++){
                    tensorCArray[i][j][k] = 0;
                }
            }
        }
    }
int Tensor:: getElem(int x){
        return tensorAArray[x];
    }
int Tensor:: getElem(int x, int y){
        return tensorBArray[x][y];
    }
int Tensor:: getElem(int x, int y, int z){
        return tensorCArray[x][y][z];
    }
void Tensor:: putElem(int coord, int value){
        tensorAArray[coord] = value;
    }
void Tensor:: putElem(vector<int> coords, int x ){
        if(coords.size() == 2){
            tensorBArray[coords[0]][coords[1]] = x;
        }
        if(coords.size()==3){
            tensorCArray[coords[0]][coords[1]][coords[2]] = x;
        }
    }
Tensor Tensor:: cut(vector<int> cutShape){
        Tensor newT(cutShape[1]-cutShape[0] + 1);
        for(int i = 0; i <= (cutShape[1]-cutShape[0]); i++){
            for(int j = cutShape[0]; j < cutShape[1]; j++){
                newT.tensorAArray[i] = (this->tensorAArray[j]);
            }
        }
        return newT;
    }
//переванттаження операцій вирізки для різних розмірностей
Tensor Tensor:: cut(vector<int> rows, vector<int> columns){
        Tensor newT(rows[1]-rows[0]+1, columns[1]-columns[0]+1);

        for(int i = 0; i<=rows[1]-rows[0]; i++){
            for(int j = 0; j<=columns[1]-columns[0]; j++){
                newT.tensorBArray[i][j] = this->tensorBArray[i+rows[0]][j+columns[0]];
            }
        }
        return newT;
    }
Tensor Tensor:: cut(vector<int> x, vector<int> y, vector<int> z){
        Tensor newT(x[1]-x[0]+1, y[1]-y[0]+1, z[1]-z[0]+1);
        for(int i = 0; i<=x[1]-x[0]; i++){
            for(int j = 0; j<= y[1]-y[0]; j++){
                for(int k = 0; k<=z[1]-z[0]; k++){
                    newT.tensorCArray[i][j][k] = this->tensorCArray[i+x[0]][j+y[0]][k+z[0]];
                }
            }
        }
        return newT;
    }
void Tensor:: reshape(int x, int y){
        vector<int> tempArray;
        for(int i = 0; i< x_t; i++){
            for(int j = 0; j < y_t; j++){
                tempArray.push_back(this->tensorBArray[i][j]);
            }
            delete tensorBArray[i];
        }
        delete tensorBArray;
        tensorBArray = new int*[x];
        for(int i = 1; i <= x; i++){
            tensorBArray[i] = new int[y];
            for(int j = 1; j <= y; j++){
                tensorBArray[i][j] = tempArray[i*j];
            }
        }
    }
void Tensor::reshape(int x, int y, int z){
        vector<int> tempArray;
        for(int i = 0; i< x_t; i++){
            for(int j = 0; j < y_t; j++){
                    for(int k = 0; k < z_t; k++){
                        tempArray.push_back(this->tensorCArray[i][j][k]);
                    }
                    delete* tensorCArray[j];
            }
            delete* tensorCArray[i];
        }
        delete* tensorCArray;
        tensorCArray = new int**[x];
        for(int i = 1; i <= x; i++){
            tensorCArray[i] = new int*[y];
            for(int j = 1; j <= y; j++){
                tensorCArray[i][j] = new int[z];
                for(int k = 1; k <= z; k++){
                    tensorCArray[i][j][k] = tempArray[i*j*k];
                }
            }
        }
    }
//перевизначення оператору додавання для поелементного додавання 2 тензорів
Tensor Tensor::operator+(Tensor a){
        if(a.y_t == NULL){
            Tensor newTensor(a.x_t);
            for(int i = 0; i < x_t; i++){
                newTensor.tensorAArray[i] = this->tensorAArray[i] + a.tensorAArray[i];
            }
            return newTensor;
        }
        if(a.z_t == NULL){
            Tensor newTensor(a.x_t, a.y_t);
            for(int i = 0; i < x_t; i++){
                for(int j = 0; j < y_t; j++){
                    newTensor.tensorBArray[i][j] = this->tensorBArray[i][j] + a.tensorBArray[i][j];
                }
            }
        } else{
            Tensor newTensor(a.x_t, a.y_t, a.z_t);
            for(int i = 0; i < x_t; i++){
                for(int j = 0; j < y_t; j++){
                    for(int k = 0; k < z_t; k++){
                        newTensor.tensorCArray[i][j][k] = this->tensorCArray[i][j][k] + a.tensorCArray[i][j][k];
                    }
                }
            }
            return newTensor;
        }
    }
//перевизначення оператору віднімання для поелементного віднімання 2 тензорів
Tensor Tensor::operator-(Tensor a){
        if(a.y_t == NULL){
            Tensor newTensor(a.x_t);
            for(int i = 0; i < x_t; i++){
                newTensor.tensorAArray[i] = this->tensorAArray[i] - a.tensorAArray[i];
            }
            return newTensor;
        }
        if(a.z_t == NULL){
            Tensor newTensor(a.x_t, a.y_t);
            for(int i = 0; i < x_t; i++){
                for(int j = 0; j < y_t; j++){
                    newTensor.tensorBArray[i][j] = this->tensorBArray[i][j] - a.tensorBArray[i][j];
                }
            }
        } else{
            Tensor newTensor(a.x_t, a.y_t, a.z_t);
            for(int i = 0; i < x_t; i++){
                for(int j = 0; j < y_t; j++){
                    for(int k = 0; k < z_t; k++){
                        newTensor.tensorCArray[i][j][k] = this->tensorCArray[i][j][k] - a.tensorCArray[i][j][k];
                    }
                }
            }
            return newTensor;
        }
    }


#endif // TENSORFINAL_H_H_INCLUDED
