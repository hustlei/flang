func main(){                //64bit pc
  let a = 1                 //Int整数常量
  let b = 1.0               //Double浮点数常量
  
  var c:Decimal = 2.55      //Decimal浮点数变量
  var d:Double = a          //自动转换为Double类型变量
  var e = 1+2j              //Complex<Int>
  var f = 1.0+j             //Complex<Double>
  var g:Complex<Double> = e //自动转换类型
  
  var c1 = 'c'                       //Char
  var c2:Character = '\u0061\u0308'  //Character  ä  
  var s1 = "hello world"             //Str
  var s2:String = "a mutable string" //String
  
  var arr1 = [1,2,3,4]               //Int[4]数组
  var arr2 = [1,2,3;1,2,3]           //Int[2,3]
  var arr3 = [[1,2],[1,2,3],[1]]     //Int[3][]
  
  var v1 = {1,3}           //Int{2} 可变长度数组
  var v2 = {1.0,3,0.0}     //Double{3}
  
  var t1 = (1,2,3)
  var t2 = ('a',2,1)
  
  var dict1 = {'a':1, 'b':2}         //Map<Char,Int>
  var dict2 = { 1:"asd"}             //Map<Int,Str> 
  
  var set1 = new Set([1,2,1,3])      //Set
  var set2 = new Set(1,'a',2)        //Set
}