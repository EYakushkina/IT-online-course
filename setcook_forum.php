<? 
  $ut=time();
  $var="REMOTE_ADDR";
  $ip=getenv($var);
  setcookie  ("UserIdCookie", $id);
  setcookie  ("UserLoginCookie", $inputlogin);
  setcookie  ("UserLogNumCookie", '101');
  setcookie  ("StartTimeCookie", $ut);
  setcookie  ("StartIPCookie", $ip);
  setcookie  ("UserAccCodeCookie", $access_code);

 echo "<SCRIPT LANGUAGE=JavaScript> location.href = \"http://aeer.cctpu.edu.ru/winn/db_forum_new/forum.phtml?pback=$pback\"; </SCRIPT>";
?>