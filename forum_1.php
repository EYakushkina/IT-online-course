<?
if( !$inlib ) { include( "lib.inc" ); db_connect(); }

include("auto.inc");
$tabusers='users_tomsk';
$tablog='log_tomsk';  // ������
$reg_true = false;
$flcreatelog = false;  //�� ��������� - �� ������ ����� ������ � ������� 
$access_code=0;   //�� ��������� - ��� ������� - ����������������

if (isset($out))
{ 
   closesession();
   // �������� ��� � �������� ����������
   echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"close_forum.php\"; </SCRIPT>";
    noregistration();
}
else
{
   if (isset($UserIdCookie))
   {  // ����������� ��� ���� ������� ���������
     $id = $UserIdCookie;
     $inputlogin = $UserLoginCookie;
     $StartT = $StartTimeCookie;
     yesregistration(0);
   }
   else
   {
     if (isset($inputlogin)) 
     {
$inputlogin = trim($inputlogin);
$inputpass = trim($inputpass);
// ���� �� � ���� ��������������� ��� � ������?
$usl='"'.$inputlogin.'"';
$res  = db_query( "SELECT id,pass,name,last_date,q_attantion,access_code from $tabusers where login like ".$usl );
$qlogin = db_num_rows( $res );
  if ($qlogin > 0) 
  {  // user ���������������, ��������� ������
     list($id,$pass,$name,$last_date,$q_attantion,$access_code) = db_fetch_row( $res );
     if ($inputpass == $pass)
     {  
        $reg_true = true; 
     }
     else {  //  �������� ������
 echo "<SCRIPT LANGUAGE=\"JavaScript\" TYPE=\"text/javascript\"> alert(\"������ ��� ������������ ".$inputlogin." �������\"); </SCRIPT>";

     }
  } 
  else  {  // ��� ������ usera
 echo "<SCRIPT LANGUAGE=\"JavaScript\" TYPE=\"text/javascript\"> alert(\"������������ � ������ ".$inputlogin." �� ���������������\"); </SCRIPT>";
  }
//����� ������� ���������� ����� �� ��������
}

if ($reg_true)
{ // ����������� ������� ��������
  $ut=time();
  $UserLogNum=0;
  $var="REMOTE_ADDR";
  $ip=getenv($var);

echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"setcook_forum.php?id=$id&inputlogin=$inputlogin&access_code=$access_code\"; </SCRIPT>";


  $StartT=$ut;
   $flcreatelog=true;   // ��� ����������� ������� ������ � �������
   yesregistration(1);

//   ----------------------------- �� ���������, ������ ����� setcookie � ������ ������  
//   $UserLogNumCookie = $UserLogNum; // ��������� � ���� ����� ������ � �������

 echo "<SCRIPT LANGUAGE=JavaScript>location.href = \"savcook.php?n=$UserLogNum&pback=$pback\"; </SCRIPT>";

}
else { // ����������� ��� �� ��������
    noregistration();
}

} // ����� else �� �������� ���� � ��� ����������� ����� �����������

} // ����� else if �� ������������ ������������

include("sess_update.inc");
updatesession();   // ��������� ����� ������, ���� ��� ���� �������

?>

