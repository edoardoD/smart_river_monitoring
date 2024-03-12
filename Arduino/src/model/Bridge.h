class Bridge
{
private:
    /* data */
public:
    Bridge();
    /**
     * @brief create all device object
     * and initialize to auto mode to detect 
     * degre of gate opening/closing 
     * ***/
    void init();
    /**
     * @brief set gate degree to open/close
     * ***/
    void setGateDegree(int degree);
    /**
     * @brief get the gate degree
     * before mooving to the next degree
     * to detect if the gate opening or closing
     * becase if the last degree is less than the
     * request degree then the gate is opening
     * otherside if current degree is graitest 
     * of request degree the gate is closing * 
     * ***/ 
    int getLastGateDegree();
    ~Bridge();
};

Bridge::Bridge(/* args */)
{
}

Bridge::~Bridge()
{
}
