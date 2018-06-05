<?

$dbname    = "rcsit";
$dbuser    = "elena";
$dbpass    = "htubjyfkmysq";
$table     = "44444";  
$inlib     = 1;
//$rootpath  = "/home/httpd/html/intel";
//$datapath  = "$rootpath/data";
$linkspath = "/var/lib/intel";
$curdate   = date( "Y-m-d H:i:s" );
$lang      = 1;
$adminmail = "yei@cctpu.edu.ru";

$desccost  = 1;
$authcost  = 1;
$newscost  = 10;
$path="";

if( !$inlang )
{
  include( $path."lang_rus.inc" );
  $text1    = $text;
  $monthes1 = $monthes;
  include( $path."lang_eng.inc" );
  $text2    = $text;
  $monthes2 = $monthes;

  if( substr(getenv("HTTP_HOST"),0,7) == "english" )
  {
    $lang = 2;
  }
  else
  {
    $text    = $text1;
    $monthes = $monthes1;
  }
}

function db_query( $q )
{
  global $dbname;
  return mysql_db_query( $dbname, $q );
}

function db_connect()
{
  global $dbname, $dbuser, $dbpass;
  mysql_connect( "localhost", "$dbuser", "$dbpass" ) or die( "Ошибка соединения с базой данных" );
  db_query( "set option character set cp1251_koi8"  );
  echo db_error();
}

function db_num_rows( $res )
{
  return mysql_num_rows( $res );
}

function db_error()
{
  return mysql_error();
}

function db_errno()
{
  return mysql_errno();
}

function db_fetch_row( $res )
{
  return mysql_fetch_array( $res );
}

function db_free_result( $res )
{
  return mysql_free_result( $res );
}

function db_insert_id()
{
  return mysql_insert_id();
}

function stripAll( $s )
{
  return stripslashes( $s );
}

function printCP($str, $port)
{
  global $PHP_SELF, $HTTP_HOST, $SERVER_PORT;

  $host = $HTTP_HOST;
  if( strpos( $host, ":" ) )
  {
    $host = substr( $host, 0, strpos( $host, ":" ) );
  }
  if( substr( $host, 0, 7 ) == "english" )
  {
    $host = substr( $host, 8 );
  }
  $dir  = substr( $PHP_SELF, 0, strrpos( $PHP_SELF, "/" ) + 1 );

  if( ($SERVER_PORT != $port) || (substr( $HTTP_HOST, 0, 7 ) == "english") )
  {
    if( $port == 80 )
    {
      echo "<a href=\"http://$host".$dir."\">".$str."</a>";
    }
    else
    {
      echo "<a href=\"http://$host:".$port.$dir."\">".$str."</a>";
    }
  }
  else
  {
    echo $str;
  }
}

function printENG()
{
  global $PHP_SELF, $HTTP_HOST;

  $host = $HTTP_HOST;
  if( strpos( $host, ":" ) )
  {
    $host = substr( $host, 0, strpos( $host, ":" ) );
  }
  $dir = substr( $PHP_SELF, 0, strrpos( $PHP_SELF, "/" ) + 1 );
  if( substr($host,0,7) != "english" )
  {
    echo "<a href=\"http://english.$host".$dir."\">english</a>";
  }
  else
  {
    echo "english";
  }
}

function tail( $num, $s )
{
  $num  = $num % 100;
  $main = substr( $s, 0, strpos( $s, ':' ) );
  $s    = substr( $s, strlen( $main ) + 1 );

  for( $i = 0; $i < 2; $i++ )
  {
    $t[$i] = substr( $s, 0, strpos( $s, "/" ) );
    $s     = substr( $s, strlen( $t[$i] ) + 1 );
  }

  $n10 = $num % 10;
  $n2  = (($n10 >= 2) && ($n10 <= 4));
  if( (($num >= 5) && ($num <= 19)) ||
      (($n10 == 0) || (($n10 >= 5) && ($n10 <= 9))) )
  {
    $tail = $main . $s;
  }
  else
  {
    if( $n2 )
    {
      $tail = $main . $t[1];
    }
    else
    {
      $tail = $main . $t[0];
    }
  }

  return $tail;
}

function getLangPrefix ( $l )
{
	$res = db_query("select code from langs where id=$l and id=lang");
	$row = db_fetch_row($res);
	db_free_result($res);
	return $row["code"];
}

function getNextID( $db )
{
  $res = db_query( "select max(id) from $db" );
  list( $id ) = db_fetch_row( $res );
  db_free_result($res);
  $id++;

  return $id;
}

function printDateTime( $stamp )
{
  global $monthes;
//echo $stamp;
  $date = date("d",$stamp)." ".$monthes[0+date("m",$stamp)]." ".date("Y",$stamp).", ".date("H:i:s",$stamp);
  return $date;
}

function printDate( $stamp )
{
  global $monthes;
  $date = date("d",$stamp)." ".$monthes[0+date("m",$stamp)]." ".date("Y",$stamp);
  return $date;
}

function clearall()
{
echo "clearall";
}

function sendMail( $m_lang, $m_body )
{
  global $text1, $text2;

  $res = db_query( "select name, email from member where lang=$m_lang" );
  while( $row = db_fetch_row( $res ) )
  {
    if( $m_lang == 1 )
    {
      mail(
      // to
      "\"".convert_cyr_string($row["name"],"w","k")."\" <".$row["email"].">",

      // subject
      convert_cyr_string($text1["newssubj"],"w","k"),

      // message
      convert_cyr_string(
      $text1["dear"].", ".$row["name"]."!\n\n".$m_body,
      "w","k"),

      // attributes
      "From: \"".convert_cyr_string($text1["maintitle"],"w","k")."\" <$adminmail>" );
    }
    if( $m_lang == 2 )
    {
      mail(
      // to
      "\"".$row["name"]."\" <".$row["email"].">",

      // subject
      $text2["newssubj"],

      // message
      $text2["dear"].", ".$row["name"]."!\n\n".$m_body,

      // attributes
      "From: \"".$text2["maintitle"]."\" <$adminmail>" );
    }
  }
  db_free_result( $res );
}

?>