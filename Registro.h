#ifndef REGISTRO_H
#define REGISTRO_H


class Registro
{
public:
    Registro(int userId, int movieId, float rating, int timestamp);
    Registro();
    ~Registro();

    void setUserId(int id);
    void setMovieId(int id);
    void setRating(float rating);
    void setTimestamp(int timestamp);

    int getUserId();
    int getMovieId();

    void ExibirRegistro();
    void ExibirUserId();

private:
    int userId;
    int movieId;
    float rating;
    int timestamp;

};

#endif // REGISTRO_H
