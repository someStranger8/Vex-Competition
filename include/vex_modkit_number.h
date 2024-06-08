//(c) Modkit.
#ifndef modkit_io_types_h
#define modkit_io_types_h

#define ____COMMA____ ,
#define MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(OPERATOR,TYPE1,TYPE2)\
friend bool operator OPERATOR  (const TYPE1 &n1,const TYPE2 &n2){\
   if(_isFloat(n1) || _isFloat(n2)){\
      return _getFloat<IntType,FloatType>(n1) OPERATOR _getFloat<IntType,FloatType>(n2);\
   }\
   else{\
      return _getInt<IntType,FloatType>(n1) OPERATOR _getInt<IntType,FloatType>(n2);\
   }\
}

#define MODKIT_IO_NUMBER_OVERLOAD_MATH(OPERATOR,THISTYPE,OTHERTYPE)\
template <typename IntType, typename FloatType> \
MODKIT_IO_Number<IntType,FloatType> operator OPERATOR (const OTHERTYPE& other, THISTYPE num) {\
    if(_isFloat(num)){\
        if(_isFloat(other)){\
            return MODKIT_IO_Number<IntType,FloatType>(_getFloat<IntType,FloatType>(other) OPERATOR  _getFloat<IntType,FloatType>(num));\
        }\
        else{\
            return MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) OPERATOR  _getFloat<IntType,FloatType>(num));\
        }\
    }\
    else{\
        if(_isFloat(other)){\
            return MODKIT_IO_Number<IntType,FloatType>(_getFloat<IntType,FloatType>(other) OPERATOR  _getInt<IntType,FloatType>(num) );\
        }\
        else{\
            return MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) OPERATOR  _getInt<IntType,FloatType>(num) );\
        }\
    }\
}

#define MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(OPERATOR,THISTYPE,OTHERTYPE)\
template <typename IntType, typename FloatType> \
MODKIT_IO_Number<IntType,FloatType> operator OPERATOR##= (OTHERTYPE& other, THISTYPE num) {\
    if(_isFloat(num)){\
        if(_isFloat(other)){\
            return other = _getFloat<IntType,FloatType>(MODKIT_IO_Number<IntType,FloatType>(_getFloat<IntType,FloatType>(other) OPERATOR  _getFloat<IntType,FloatType>(num)));\
        }\
        else{\
            return other = _getInt<IntType,FloatType>(MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) OPERATOR  _getFloat<IntType,FloatType>(num)));\
        }\
    }\
    else{\
        if(_isFloat(other)){\
            return other = _getFloat<IntType,FloatType>(MODKIT_IO_Number<IntType,FloatType>(_getFloat<IntType,FloatType>(other) OPERATOR  _getInt<IntType,FloatType>(num) ));\
        }\
        else{\
            return other = _getInt<IntType,FloatType>(MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) OPERATOR  _getInt<IntType,FloatType>(num) ));\
        }\
    }\
}

#define MODKIT_IO_NUMBER_OVERLOAD_DIVISION(THISTYPE,OTHERTYPE)\
template <typename IntType, typename FloatType>\
MODKIT_IO_Number<IntType,FloatType> operator / (const OTHERTYPE& other, THISTYPE num) {\
    if(_isFloat(num)){\
      if(_isFloat(other)){\
         return MODKIT_IO_Number<IntType,FloatType>(_getFloat<IntType,FloatType>(other) /  _getFloat<IntType,FloatType>(num));\
      }\
      else{\
         return MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) /  _getFloat<IntType,FloatType>(num));\
      }\
    }\
    else{\
      if(_isFloat(other)){\
         return MODKIT_IO_Number<IntType,FloatType>(_getFloat<IntType,FloatType>(other) /  _getInt<IntType,FloatType>(num) );\
      }\
      else{/*always have one float when dividing*/\
         return MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) /  _getFloat<IntType,FloatType>(num) );\
      }\
    }\
}

#define MODKIT_IO_NUMBER_OVERLOAD_BINARY(OPERATOR,THISTYPE,OTHERTYPE)\
template <typename IntType, typename FloatType> \
MODKIT_IO_Number<IntType,FloatType> operator OPERATOR (const OTHERTYPE& other, THISTYPE num) {\
    return MODKIT_IO_Number<IntType,FloatType>(_getInt<IntType,FloatType>(other) OPERATOR  _getInt<IntType,FloatType>(num) );\
}


namespace MODKIT_IO_NUMBER_NAMESPACE{
    //this enum needs to be outside class or adds to sizeof(instance)
    typedef enum {INT, FLOAT} __attribute__((packed)) Number_Type;
    
    //type helpers
    inline bool _isInt(int i){return true;}
    inline bool _isInt(long l){return true;}
    inline bool _isInt(float f){return (f==(int)f);}
    inline bool _isInt(double d){return (d==(int)d);}
    inline bool _isFloat(int i){return false;}
    inline bool _isFloat(long l){return false;}
    inline bool _isFloat(float f){return (f!=(int)f);}
    inline bool _isFloat(double d){return (d!=(int)d);}

    
    template <typename IntType, typename FloatType> IntType _getInt(int i){return (IntType)i;}
    template <typename IntType, typename FloatType> IntType _getInt(long l){return (IntType)l;}
    template <typename IntType, typename FloatType> IntType _getInt(float f){return (IntType)f;}
    template <typename IntType, typename FloatType> IntType _getInt(double d){return (IntType)d;}
    template <typename IntType, typename FloatType> FloatType _getFloat(int i){return (FloatType)i;}
    template <typename IntType, typename FloatType> FloatType _getFloat(long l){return (FloatType)l;}
    template <typename IntType, typename FloatType> FloatType _getFloat(float f){return (FloatType)f;}
    template <typename IntType, typename FloatType> FloatType _getFloat(double d){return (FloatType)d;}
    
    //forward declare number class for forward declare type helpers
    template <typename IntType = long, typename FloatType=double>class MODKIT_IO_Number;
    
    //forward declare number class type helpers
    template <typename IntType, typename FloatType> bool _isInt(MODKIT_IO_Number<IntType,FloatType> num);
    template <typename IntType, typename FloatType> bool _isFloat(MODKIT_IO_Number<IntType,FloatType> num);
    
    template <typename IntType, typename FloatType> IntType _getInt(MODKIT_IO_Number<IntType,FloatType> num);
    template <typename IntType, typename FloatType> FloatType _getFloat(MODKIT_IO_Number<IntType,FloatType> num);
    
    template <typename IntType, typename FloatType>
    class MODKIT_IO_Number{
    public:
        
        MODKIT_IO_Number(int _n):type(INT),n(_n){ };
        MODKIT_IO_Number(long _l):type(INT),n(_l){ };
        MODKIT_IO_Number(float _f):type(FLOAT),f(_f){if(_isInt(f)){type=INT; n=_getInt<IntType,FloatType>(f);} };
        MODKIT_IO_Number(double _d):type(FLOAT),f(_d){if(_isInt(f)){type=INT; n=_getInt<IntType,FloatType>(f);}};
        MODKIT_IO_Number():type(INT),n(0){}
        bool isInt() const {
            return type==INT;
        }
        bool isFloat() const {
            return type==FLOAT;
        }
        
        FloatType getFloat() const {
            if(type==FLOAT)
                return f;
            else
                return n;          
        }
        
        IntType getInt() const {        
            if(isFloat())
                return f;
            else
                return n;
        }
        
        operator FloatType () { return getFloat(); }
        operator IntType ()  { return getInt(); }        

        operator uint16_t () { return (uint16_t) getInt(); }        
        operator  int16_t () { return ( int16_t) getInt(); }        
        operator uint32_t () { return (uint32_t) getInt(); }        
        // may not need this one
        //operator  int32_t () { return ( int32_t) getInt(); }        
        
         /* Greater than > operator */
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, IntType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, FloatType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    
        
        /* Less than < operator */
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, IntType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, FloatType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        
        
        /* Greater than or eqaual to >= operator */
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, IntType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, FloatType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>=,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(>=,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        
        /* Less than or equal to <= operator */
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, IntType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, FloatType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<=,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(<=,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        
        /* Equal to == operator */
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(==,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(==,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, IntType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(==,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, FloatType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(==,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(==,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        
        /* Not equal to != operator */
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(!=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(!=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, IntType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(!=,MODKIT_IO_Number<IntType ____COMMA____ FloatType>, FloatType);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(!=,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        MODKIT_IO_NUMBER_OVERLOAD_COMPARISON(!=,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
        
        // Shift left <<
        MODKIT_IO_Number<IntType,FloatType> operator<< ( int v ) {
            return this->getInt() << v;
        }
        // Shift right >>
        MODKIT_IO_Number<IntType,FloatType> operator>> ( int v ) {
            return this->getInt() >> v;
        }
        // shift left and assign <<=
        MODKIT_IO_Number<IntType,FloatType> operator<<= ( int v ) {
            *this = (this->getInt() << v);
            return *this;
        }
        // shift right and assign >>=
        MODKIT_IO_Number<IntType,FloatType> operator>>= ( int v ) {
            *this = (this->getInt() >> v);
            return *this;
        }        

        //MODKIT_IO_Number<IntType,FloatType> operator^ ( IntType v ) {
        //    return (this->getInt() ^ v);
        //}

        // ostream <<
        friend std::ostream& operator<< (std::ostream& stream, MODKIT_IO_Number<IntType,FloatType> n ) {
            if( n.isFloat() )
                stream << n.getFloat();
            else
                stream << n.getInt();
            return stream;
        }
        
                
        MODKIT_IO_Number<IntType,FloatType>& operator++();
        MODKIT_IO_Number<IntType,FloatType> operator++(int);
        MODKIT_IO_Number<IntType,FloatType>& operator--();
        MODKIT_IO_Number<IntType,FloatType> operator--(int);

        MODKIT_IO_Number<IntType,FloatType> operator-();
        
    private:
        
        Number_Type type;
        union {
            IntType n;
            FloatType f;
        };
        
    };
    
    

    
    
    /* Addtition + operator */
    MODKIT_IO_NUMBER_OVERLOAD_MATH(+,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(+,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(+,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(+,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(+,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);

    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(+,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(+,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(+,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(+,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(+,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);

    
    /* Subtraction - operator */
    MODKIT_IO_NUMBER_OVERLOAD_MATH(-,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(-,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(-,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(-,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(-,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);

    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(-,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(-,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(-,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(-,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH_ASSIGN(-,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);
    
    /* Multiplication * operator */
    MODKIT_IO_NUMBER_OVERLOAD_MATH(*,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(*,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(*,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(*,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_MATH(*,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);
    
    
    /* Division / operator */
    MODKIT_IO_NUMBER_OVERLOAD_DIVISION(MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_DIVISION(IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_DIVISION(MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_DIVISION(FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_DIVISION(MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);
    
    // bitwise xor
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(^,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(^,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(^,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(^,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(^,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);
    // bitwise and
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(&,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(&,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(&,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(&,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(&,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);
    // bitwise or
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(|,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(|,IntType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(|,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,IntType);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(|,FloatType,MODKIT_IO_Number<IntType ____COMMA____ FloatType>);
    MODKIT_IO_NUMBER_OVERLOAD_BINARY(|,MODKIT_IO_Number<IntType ____COMMA____ FloatType>,FloatType);

    
    
    //actual _isType helper declarations
    template <typename IntType, typename FloatType> bool _isInt(MODKIT_IO_Number<IntType,FloatType> num){
        return num.isInt();
    }
    template <typename IntType, typename FloatType> bool _isFloat(MODKIT_IO_Number<IntType,FloatType> num){
        return num.isFloat();
    }
    
  

    template <typename IntType, typename FloatType> IntType _getInt(MODKIT_IO_Number<IntType,FloatType> num){
        return num.getInt();
    }
    template <typename IntType, typename FloatType> FloatType _getFloat(MODKIT_IO_Number<IntType,FloatType> num){
        return num.getFloat();
    }

  
    template <typename IntType, typename FloatType>
    MODKIT_IO_Number<IntType,FloatType>& MODKIT_IO_Number<IntType,FloatType> ::operator++()
    {
        (type==FLOAT) ? f++ : n++ ;
        return *this;
    }
    
    template <typename IntType, typename FloatType>
    MODKIT_IO_Number<IntType,FloatType> MODKIT_IO_Number<IntType,FloatType> ::operator++(int)
    {
        MODKIT_IO_Number temp = *this;
        ++*this;
        return temp;
    }
    template <typename IntType, typename FloatType>
    MODKIT_IO_Number<IntType,FloatType>& MODKIT_IO_Number<IntType,FloatType> ::operator--()
    {
        (type==FLOAT) ? f-- : n-- ;
        return *this;
    }
    
    template <typename IntType, typename FloatType>
    MODKIT_IO_Number<IntType,FloatType> MODKIT_IO_Number<IntType,FloatType> ::operator--(int)
    {
        MODKIT_IO_Number temp = *this;
        --*this;
        return temp;
    }

    template <typename IntType, typename FloatType>
    MODKIT_IO_Number<IntType,FloatType> MODKIT_IO_Number<IntType,FloatType> ::operator-()
    {
        MODKIT_IO_Number temp = *this;
        temp.f = -temp.f;
        temp.n = -temp.n;
        return temp;
    }
}


//c++11 - using  number = MODKIT_IO_NUMBER_NAMESPACE::MODKIT_IO_Number<>;
//typedef  MODKIT_IO_NUMBER_NAMESPACE::MODKIT_IO_Number<>  number;
//VEX IQ needs float not double or it crashes (3 second timeout)!
typedef  MODKIT_IO_NUMBER_NAMESPACE::MODKIT_IO_Number<int,double>  number;
typedef  bool boolean;

#endif // ifndef modkit_io_types_h
