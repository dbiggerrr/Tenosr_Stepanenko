#include <iostream>
#include <vector>

#ifndef TENCOR_H_H_INCLUDED
#define TENCOR_H_H_INCLUDED

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
private:
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
Tensor::int getElem(int x){
        return tensorAArray[x];
    }
Tensor::int getElem(int x, int y){
        return tensorBArray[x][y];
    }
Tensor::int getElem(int x, int y, int z){
        return tensorCArray[x][y][z];
    }
Tensor::void putElem(int coord, int value){
        tensorAArray[coord] = value;
    }
Tensor::void putElem(vector<int> coords, int x ){
        if(coords.size() == 2){
            tensorBArray[coords[0]][coords[1]] = x;
        }
        if(coords.size()==3){
            tensorCArray[coords[0]][coords[1]][coords[2]] = x;
        }
    }
Tensor::Tensor cut(vector<int> cutShape){
        Tensor newT(cutShape.size());
        for(int i = 0; i < (cutShape[1]-cutShape[0]); i++){
            for(int j = cutShape[0]; j < cutShape[1]; j++){
                newT.tensorAArray[i] = (this->tensorAArray[j]);
            }
        }
    }
Tensor::Tensor cut(vector<int> rows, vector<int> columns){
        Tensor newT(rows[1]-rows[0]+1, columns[1]-columns[0]+1);
        //int tempArray[rows.size()*columns.size()];
        vector<int> tempArray;
        for(int i = rows[0]; i<rows[1]; i++){
            for(int j = columns[0]; j<columns[1]; j++){
                tempArray.push_back(this->tensorBArray[i][j]);
            }
        }
        for(int i = 1; i <= (rows[1]-rows[0]); i++){
            for(int j = 1; j <= (columns[1]-columns[0]); j++){
                newT.tensorBArray[i][j] = tempArray[i*j];
            }
        }

    }
Tensor::Tensor cut(vector<int> x, vector<int> y, vector<int> z){
        Tensor newT(x[1]-x[0], y[1]-y[0], z[1]-z[0]);
        vector<int> tempArray;
        for(int i = x[0]; i<x[1]; i++){
            for(int j = y[0]; j<y[1]; j++){
                for(int k = z[0]; k<z[1]; k++){
                    tempArray.push_back(this->tensorCArray[i][j][k]);
                }
            }
        }
        for(int i = 1; i <= (x[1]-x[0]); i++){
            for(int j = 1; j <= (y[1]-y[0]); j++){
                for(int k = 1; k <= (z[1]-z[0]); k++){
                    newT.tensorCArray[i][j][k] = tempArray[i*j*k];
                }
            }
        }
    }
Tensor::void reshape(int x, int y){
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
Tensor::void reshape(int x, int y, int z){
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
        delete* tensorBArray;
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
Tensor::Tensor operator+(Tensor a){
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
Tensor::Tensor operator-(Tensor a){
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
#endif // TENCOR_H_H_INCLUDED
