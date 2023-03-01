function buttonGroupPressed (event){
    const feedback = document.getElementById("feedback");
    if(event.target.className =="correct"){
        event.target.style.backgroundColor = "green";
        feedback.innerHTML = "Your answer is : correct !";
    }
    else {
        event.target.style.backgroundColor ="red";
        feedback.innerHTML = "Your answer is : inccorect ";
    }
}


function Submit(){
    const feedback_2 = document.getElementById("feedback-2");
    const input_element = document.getElementById("answer");
    const answer = input_element.value ;
    const correct_answer = "Meningitis is the inflammation of the fluid and membranes surrounding the brain and spinal cord";
    if (answer == correct_answer){
        input_element.style.backgroundColor = "green";
        feedback_2.innerHTML="Your answer is : correct !";

    }
    else {
        input_element.style.backgroundColor ="red";
        feedback_2.innerHTML = "Your answer is : incorrect";
    }
}