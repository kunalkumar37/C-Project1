//problem:: given a gps co-ordinate of a person who needs a cab and co ordinate of all the cabs in the city 
//stored in text file in JSON format find the user id and name of all the cab drivers available in 50 km 
//Input : file customers.json which contains GPS co-ordinates of a person who needs a cab in degrees and co-ordinates of all the cabs in the city stored in a text file in JSON format.

//Output : file answers.json which contains user-id and Name of all the cab drivers available in 50 km proximity stored in a new file.

#include<bits/stdc++.h>
using namespace std;
#define lat1d 12.9611159
#define lon1d 77.6362214
//these upper two are latitude and longitude of customers
#define pi 3.14159265358979323846
#define earth_radius 6371.0

ifstream customer_list("customer.json");
ofstream out("answer.json");

//function to convert deg to radian
double degtorad(double deg){
    return (deg*pi/180);
}

//applying great distance formula 
double distanceEarth(double lat2d,double lon2d){
    double lat1,lon1,lat2,lon2,delta_lon,central_ang;
    lat1=degtorad(lat1d);
    lon1=degtorad(lon1d);
    lat2=degtorad(lat2d);
    lon2=degtorad(lon2d);

    delta_lon=lon2-lon1;

    //great circle distance formula
    central_ang=acos(sin(lat1)* sin(lat2)+cos(lat1)*cos(lat2)*cos(delta_lon));

    return (earth_radius*central_ang);
}

struct json{

    long long int length,i,j,x,y,m,n,f,fi,id[100000];

    char latitude_as_string[1000],
    longitude_as_string[1000],
    id_as_string[1000],name[1000];

    double lat2d,lon2d;
    string line;

    void distance_calulator(){
        if(distanceEarth(lat2d,lon2d)<=50.0000){
            //converting id to int format
            id[i]=atoll(id_as_string);
            i++;
            out<<"{\"user_id\":"<<endl<<id[i-1]<< ", \"name\": " << name << "}" << endl;
        }
    }

    // function to read various attributes
    //using json attribute
    void json_parser(){
        if(customer_list.is_open()){
            while(getline(customer_list,line)){
                f=0;
                x=0;y=0;fi=0;m=0;n=0;
                length=line.size();
                for(j=0;j<length;j++){
                    if(line[j]=='"'){
                        f++;
                    }
                    else if(line[j]==':'){
                        fi++;
                    }
                    if(f==3){
                        j++;
                        while(line[j]!='"'){
                            latitude_as_string[x]=line[j];
                            x++;
                            j++;

                        }
                        j--;
                        latitude_as_string[x]='\0';

                    }

                    else if(f==13){
                        j++;
                        while(line[j]!='"'){
                            longitude_as_string[y]=line[j];
                            y++;
                            j++;

                        }
                        j--;
                        longitude_as_string[y]='\0';

                    }

                    if(fi==2){
                        j+=2;
                        while(line[j]!=','){
                            id_as_string[m]=line[j];

                        }

                        j--;
                        id_as_string[m]='\0';
                        fi++;
                    }
                    else if(fi==4){
                        j+=2;
                        while(line[j]!=','){
                            name[n]=line[j];
                            n++;
                            j++;

                        }
                        j--;
                        name[n]='\0';
                        fi++;
                        f+=2;
                    }
                }
                lat2d = atof(latitude_as_string);
                lon2d = atof(longitude_as_string);
                distance_calulator();
            }
        }

        customer_list.close();
        //closing stream of customers file

        out.close();
        //closing stream of answers file
    }

};

int main(){
    json obj;
    obj.json_parser();
    return 0;
}