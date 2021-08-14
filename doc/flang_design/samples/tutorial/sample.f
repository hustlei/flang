domain proj
use sys.*

/* 程序入口函数
注释中加入转义字符\r\n
main函数注释*/
pub func main(){
  var a=5
  let b:float=-0.5e+23    //a float num
  var x,_ = a%%b;
  let s="\xHH\uABCD\t\r\"a string"  //"a string comment
  let c=1+j
  var 我 = "一个unicode字符串。"  /* comment "asdf*/
  var 不转义字符串="""\t不转义的\n
  字符串"子字符串""""
  println("hello, world!");
  println(add(1,2))
  
  let c='我'
  let ch='B̊'
}


#[inline]
func add(a:int, b:int):int{
   a+b
}


