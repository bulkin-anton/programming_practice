#include <iostream>

class Logger{
    public:
        static Logger& getLogger(int);
        static void set_global_severity(int);
        void set_severity(int);
        int get_severity() const;
        void log(const char *) const;
    private:
        Logger();
        Logger(const Logger&){};
        int local_severity = 0;
        static Logger& add_logger(int);
        struct Arr{
            int key;
            Logger *obj;
        };
        class Loggers{
            public:
                int global_severity;
                Arr *logs;
                int num_loggers;
                ~Loggers();
        };
        static Loggers status;
};

Logger::Loggers Logger::status = {0, 0, 0};

Logger::Logger(){
    local_severity = 0;
}

Logger&
Logger::getLogger(int key){
    for (int i = 0; i < status.num_loggers; i++){
        if (key == status.logs[i].key){
            return *status.logs[i].obj;
        }
    }
    return add_logger(key);
}

Logger&
Logger::add_logger(int key){
    Arr *new_logs = new Arr[++status.num_loggers];
    for (int i = 0; i < (status.num_loggers - 1); i++){
        new_logs[i] = status.logs[i];
    }
    new_logs[status.num_loggers - 1].key = key;
    new_logs[status.num_loggers - 1].obj = new Logger;
    delete []status.logs;
    status.logs = new_logs;
    return *status.logs[status.num_loggers - 1].obj;
}

void
Logger::set_global_severity(int n){
    status.global_severity = n;
}

int
Logger::get_severity() const{
    return local_severity;
}

void
Logger::set_severity(int n){
    local_severity = n;
}

void
Logger::log(const char *str) const{
    if (local_severity >= status.global_severity){
        std::cout << str << std::endl;
    }
}

Logger::Loggers::~Loggers(){
    for (int i = 0; i < num_loggers; i++){
        delete logs[i].obj;
    }
    delete []logs;
}
