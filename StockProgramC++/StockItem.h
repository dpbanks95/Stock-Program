/* 
 * File:   StockItem.h
 * Author: Daniel Banks
 */

#ifndef STOCKITEM_H
#define	STOCKITEM_H

class StockItem {
protected:
    std::string type;
    std::string stockCode;
    int stockLevel;
    int price;
    
public:
    StockItem(std::string type, std::string stockCode,int stockLevel,int price);
    StockItem(const StockItem& orig){}
    virtual ~StockItem();
    
    std::string getType(){return type;}
    std::string getStockCode(){return stockCode;}
    int getStockLevel(){return stockLevel;}
    int getPrice(){return price;}

    void setType(std::string newType){type = newType;}
    void setStockCode(std::string newStockCode){stockCode = newStockCode;}
    void setStockLevel(int newStockLevel){stockLevel = newStockLevel;}
    void setPrice(int newPrice){price = newPrice;}
    virtual void printItem() = 0;
    virtual std::string getDetails() = 0;
};

class Resistor: public StockItem{
private:
    std::string resistance;
public:
    ~Resistor(){}
    Resistor(std::string type, std::string stockCode, int stockLevel, int price,
    std::string resistance);
    virtual std::string getDetails(){return resistance;}
    void setResistance(std::string newResistance){resistance = newResistance;}
    void printItem();
};

class Capacitor: public StockItem{
private:
    std::string capacitance;
public:
    ~Capacitor(){}
    Capacitor(std::string type, std::string stockCode, int stockLevel,int price,
    std::string capacitance);
    virtual std::string getDetails(){return capacitance;}
    void setCapacitance(std::string newCapacitance){capacitance=newCapacitance;}
    void printItem();
};

class Diode: public StockItem{
public:
    ~Diode(){}
    Diode(std::string type, std::string stockCode, int stockLevel, int price);
    virtual std::string getDetails(){return "";}
    void printItem();
};

class Transistor: public StockItem{
private:
    std::string deviceType;
public:
    ~Transistor(){}
    Transistor(std::string type, std::string stockCode, int stockLevel, 
    int price, std::string deviceType);
    virtual std::string getDetails() {return deviceType;}
    void setDeviceType(std::string newDeviceType){deviceType = newDeviceType;}
    void printItem();
};

class IntegratedCircuit: public StockItem{
private:
    std::string description;
public:
    ~IntegratedCircuit(){}
    IntegratedCircuit(std::string type, std::string stockCode, int stockLevel, 
    int price, std::string description);
    virtual std::string getDetails(){return description;}
    void setDescription(std::string newDescription){description=newDescription;}
    void printItem();
};

#endif	/* STOCKITEM_H */

