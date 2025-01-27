# ula
 
<h1>OVERVIEW</h1>

<div>ULA is a formula computation engine made for C. It's intened functionality is meant to remove the need for creating several distinct mathematical functions in a given project, and open the door for complex formula manipulation operations through substringing and concatination.</div>

![Animation](https://github.com/user-attachments/assets/96a92e8f-0628-4d8d-aae9-3f57c2852aaf)

<h1>USAGE</h1>
<div>ULA supports nested paranthesis logic, exponentials (including roots), and standard arithmetic and scalar operations (addition, subtraction, multiplication, and division) </div>
<br>
<div>ULA works by fully evaluating each term as either a function,coeficent, or varible, and then summing the result of evaluating each of those terms.  Functions are defined as terms that contain multiplcaiton, division, paranthesis, or any of such kind of compound terms. (3X^2 is a function for example). Coefiencets simply float numbers (1431.4314) and ofcourse vars are the defined vars (X,Y,etc) </div>
<br>
<div>With those definitions in place, here is how you use ULA</div>
<br>
<div>First create a function string with the following format</div>
<br>
<ol>
  <li><strong>Std Arthmetic:</strong> (function/coef/var) +/-/* (function/coef/var)(</li>
  <li><strong>Division:</strong> (function/coef/var) / (function/coef/var)</li>
  <li><strong>Exponential:</strong> (function/coef/var) / (function/coef/var)</li>
  <li><strong>Parantheis:</strong> ( (function/coef/var) ) {operator} (function/...)</li>
</ol> 
<br>
<div>**Note:** To use roots you simply use a number less that 1 (x^0.5 = sqrt(x))</div>
<br>
<div>Here are some examples to help</div>
<ol>
  <li>((3*X^(22X^Y))+19)/2(</li>
  <li>20^(X)+Y^(0.5)</li>
  <li>Y*X^3</li>
</ol> 
<div>To declare varibles, use <strong>STRICTLY UPPER CASE LETTERS.</strong> To defined those varibles, simply create a mapping string that follows the format <strong>"VAR1:floatVal,VAR2:floatVal,..."</strong></div>
<br>
<div>for example: <strong>"X:10,YDSA:231.321"</strong></div>
<br>
<div>once you have a function string and a vars string, you pass those two values into the strToFuncEval(func,vars) function and recieve a float</div>
<h1>SET UP</h1>

<div>Simply download the ula.h file into the project you'd like to use it in, and at the top of you src code's write <strong>#include "path/to/ula.h"</strong> From there you'll have access to the <strong>strToFuncEval(func,vars)</strong> function</div>

![image](https://github.com/user-attachments/assets/6654ba6c-0c3d-4963-9efe-1b46308f4268)

<h1>TECHNICAL INFORMATION</h1>

<div> The roots of numbers are computed using bisection method. We alter the problem as such: </div>
<br>

![image](https://github.com/user-attachments/assets/2f5b28ec-5ed7-4d44-a6d4-6a86e8171826)

<br>
<div> Then bisection method is used to sovle for the roots </div>
<br>

![Bisection_method svg](https://github.com/user-attachments/assets/1874da6d-52f6-464d-a85b-b6b3e77fe606)


<h1>CAUTION</h1>

<div>You may notice you can use implied muliplication like 3X, or (10X)(5Y). I strongly recomend avoiding using implied multiplcation, please use * instead. It is very buggy are the momment and could lead to issues.</div>
<br>
<div>varible names <strong>can only be 128 characters long,</strong> also you can only have at most 128 varibles in a given project</div>
