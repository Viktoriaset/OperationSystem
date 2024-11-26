#pragma once

class IBase
{
protected:
    virtual ~IBase() = default; // защищенный деструктор

public:
    virtual void Delete() = 0;  // удаляет объект

    IBase& operator=(const IBase&) = delete; // запрет присваивания
};
