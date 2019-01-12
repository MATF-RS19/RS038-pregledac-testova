#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "image_processing.hpp"
#include <iostream>
#include <string>
#include <vector>

cv::Mat binarizacija(cv::Mat &img){

    cv::GaussianBlur(img, img, cv::Size(3,3),0);
    cv::adaptiveThreshold(img, img,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10);
    cv::bitwise_not(img, img);
    return img;
}

//funkcija preuzeta sa interneta, vraca tacku preseka 2 prave
cv::Point2f izracunajPresek(cv::Vec4i a, cv::Vec4i b) {
    
    int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
    int x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];

    if (float d = ((float)(x1-x2) * (y3-y4)) - ((y1-y2) * (x3-x4)))
    {
        cv::Point2f pt;
        pt.x = ((x1*y2 - y1*x2) * (x3-x4) - (x1-x2) * (x3*y4 - y3*x4)) / d;
        pt.y = ((x1*y2 - y1*x2) * (y3-y4) - (y1-y2) * (x3*y4 - y3*x4)) / d;
        return pt;
    } 
    else
        return cv::Point2f(-1, -1);
}

bool comparator(cv::Point2f a, cv::Point2f b){ return a.x<b.x; }
bool comparator2(double a, double b) { return a<b; }
bool comparator3(cv::Vec3f a, cv::Vec3f b) { return a[0]<b[0]; }

void sortirajCoskove(std::vector<cv::Point2f>& coskovi, cv::Point2f centar) {

    //kreiramo vektor tacaka, dva gornja coska i dva gornja
    std::vector<cv::Point2f> gore, dole;
    for (int i = 0; i < coskovi.size(); i++) {
        if (coskovi[i].y < centar.y)
            gore.push_back(coskovi[i]);
        else
            dole.push_back(coskovi[i]);
    }
    sort(gore.begin(),gore.end(), comparator);
    sort(dole.begin(),dole.end(), comparator);

    cv::Point2f gl = gore[0];
    cv::Point2f gd = gore[gore.size()-1];
    cv::Point2f dl = dole[0];
    cv::Point2f dd = dole[dole.size()-1];
    
    coskovi.clear();
    coskovi.push_back(gl);
    coskovi.push_back(gd);
    coskovi.push_back(dd);
    coskovi.push_back(dl);

}

std::vector<std::string> izolovanje_pravougaonika(cv::Mat & img){

    std::vector<std::string> user_input;
    cv::Mat img_raw;
    cv::cvtColor(img, img_raw, CV_GRAY2RGB);

    cv::imwrite("ucitani_fajl.jpg",img);

    img = binarizacija(img);

    //trazimo linije cetvorougla tj okvir testa
    std::vector<cv::Vec4i> linije;
    cv::HoughLinesP(img, linije, 1, CV_PI/180, 80, 400, 10);

    //trazimo preseke linija, ondosno coskove cetvorougla
    std::vector<cv::Point2f> coskovi;
    for (int i = 0; i < linije.size(); i++) {
        for (int j = i+1; j < linije.size(); j++) {
            cv::Point2f pt = izracunajPresek(linije[i], linije[j]);
            if (pt.x >= 0 && pt.y >= 0 && pt.x < img.cols && pt.y < img.rows)
                coskovi.push_back(pt);
        }
    }

    cv::Point2f centar(0,0);
    for (int i = 0; i < coskovi.size(); i++)
    centar += coskovi[i];
    centar *= (1. / coskovi.size());

    sortirajCoskove(coskovi, centar);

    //formiramo novi kvadrat koji nije warp-ovan u prostoru 
    cv::Rect r = cv::boundingRect(coskovi);
    cv::Mat kvadrat = cv::Mat::zeros(r.height, r.width, CV_8UC3);
    std::vector<cv::Point2f> kvadrat_pts;
    kvadrat_pts.push_back(cv::Point2f(0, 0));
    kvadrat_pts.push_back(cv::Point2f(kvadrat.cols, 0));
    kvadrat_pts.push_back(cv::Point2f(kvadrat.cols, kvadrat.rows));
    kvadrat_pts.push_back(cv::Point2f(0, kvadrat.rows));

    // ispravljamo perspektivu
    cv::Mat transmtx = cv::getPerspectiveTransform(coskovi, kvadrat_pts);
    cv::warpPerspective(img_raw, kvadrat, transmtx, kvadrat.size());

    cv::imwrite("perspektiva.jpg",kvadrat);

    //cuvamo binarnu kopiju ispravljene slike..
    cv::Mat kvadrat_bin;
    cv::cvtColor(kvadrat, kvadrat_bin ,CV_BGR2GRAY);
    kvadrat_bin = binarizacija(kvadrat_bin);
    
    cv::imwrite("binarizacija.jpg", kvadrat_bin);

    //detektovanje centra kruga
    cv::Mat krugovi_img;
    cvtColor(kvadrat, krugovi_img, CV_BGR2GRAY);
    std::vector<cv::Vec3f> krugovi;  
    HoughCircles(krugovi_img, krugovi, CV_HOUGH_GRADIENT, 1, img.rows/8, 100, 75, 0, 0 );  
    
    for( size_t i = 0; i < krugovi.size(); i++ ){  
        cv::Point centar(cvRound(krugovi[i][0]), cvRound(krugovi[i][1]));
        // centar kruga  
        circle(kvadrat, centar, 3, cv::Scalar(0,255,0), -1, 8, 0 );
    }
    cv::imwrite("detektovan_centar.jpg",kvadrat);

    double prosek_r = 0;
    std::vector<double> row;
    std::vector<double> col;

    for(int i = 0; i < krugovi.size(); i++) {
        
        bool nadjeno = false;
        int r = cvRound(krugovi[i][2]);
        prosek_r += r;
        int x = cvRound(krugovi[i][0]);
        int y = cvRound(krugovi[i][1]);

        for(int j = 0; j < row.size(); j++) {
            double y2 = row[j];
            if(y - r < y2 && y + r > y2) {
                nadjeno = true;
                break;
            }
        }
        if(!nadjeno){
            row.push_back(y);
        }
        nadjeno = false;
        for(int j=0;j<col.size();j++){
            double x2 = col[j];
            if(x - r < x2 && x + r > x2){
                nadjeno = true;
                break;
            }
        }
        if(!nadjeno){
            col.push_back(x);
        }
    }

    prosek_r /= krugovi.size();

    std::sort(row.begin(),row.end(),comparator2);
    std::sort(col.begin(),col.end(),comparator2);

    for( int i = 0; i < row.size(); i++) {
        
        double max = 0;
        double y = row[i];
        int ind = -1;
    
        for(int j = 0; j < col.size(); j++) {
            double x = col[j];
            cv::Point c(x,y);

            for(int k = 0; k < krugovi.size(); k++){
            
                double x2 = krugovi[k][0];
                double y2 = krugovi[k][1];
            
                if(abs(y2-y)<prosek_r && abs(x2-x)<prosek_r){
                    x = x2;
                    y = y2;
                }
            }

            cv::circle(kvadrat, c, prosek_r, cv::Scalar(0,0,255), 3, 8, 0 );
            cv::Rect rect(x-prosek_r, y-prosek_r, 2*prosek_r, 2*prosek_r);
            cv::Mat submat = kvadrat_bin(rect);
            double p = (double)countNonZero(submat) / (submat.size().width * submat.size().height);
            //detekcija popunjenosti kruga(ako je veca od 37.5 posto smatra se zaokruzenim resenjem)
            if( p >= 0.375 && p > max){
                max = p;
                ind = j;
            }
        }
        //stampanje resenja
        if(ind == -1) {
            user_input.push_back("-");
        }
        else {
            const char c[2] = {'A' + ind, '\0'};
            std::string stri(c);
            user_input.push_back(stri);
        }
    }

    cv::imwrite("final.jpg",kvadrat);
    for(int i = 0; i < user_input.size(); i++){
        std::cout << user_input[i] << std::endl;
    }
    return user_input;

}
