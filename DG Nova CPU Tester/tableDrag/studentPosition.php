<?php
foreach ($_POST["value"] as $key => $value) {
    $data["Position"]=$key+1;
    updatePosition($data, $value);
}
echo "Sorting Done";
function updatePosition($data,$id){
    $con=  mysqli_connect("localhost", "root", "", "phptutorial");
    if(array_key_exists("Name", $data)){
        $data["Name"]=$this->real_escape_string($data["Name"]);
    }
    foreach ($data as $key => $value) {
        $value="'$value'";
        $updates[]="$key=$value";
    }
    $imploadAray=  implode(",", $updates);
    $query="Update studentinfo Set $imploadAray Where Id='$id'";
    $result=  mysqli_query($con,$query) or die(mysqli_error($con));
        if($result){
            return "Category is position";
        }
        else
        {
            return "Error while updating position";
        }
}
