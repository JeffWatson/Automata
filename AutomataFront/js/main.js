$(document).ready(function () {
    // variable to hold request
    var request;
    // bind to the submit event of our form
    $("#regex-form").submit(function (event) {
        // abort any pending request
        if (request) {
            request.abort();
        }
        // setup some local variables
        var $form = $(this).parents("form");
        // let's select and cache all the fields
        var $inputs = $form.find("input, select, button, textarea");
        // serialize the data in the form
        var serializedData = $form.serialize();

        // let's disable the inputs for the duration of the ajax request
        $inputs.prop("disabled", true);

        // fire off the request to /form.php
        request = $.ajax({
            url: "/apps/Automata/php/handlers/automata_handler.cgi",
            type: "POST",
            data: serializedData
        });

        // callback handler that will be called on success
        request.done(function (response, textStatus, jqXHR) {
            // log a message to the console
            console.log("Hooray, it worked! Response: " + response);
            handleResponse(response);
        });

        // callback handler that will be called on failure
        request.fail(function (jqXHR, textStatus, errorThrown) {
            // log the error to the console
            console.error(
                "The following error occured: " +
                    textStatus, errorThrown
            );
        });

        // callback handler that will be called regardless
        // if the request failed or succeeded
        request.always(function () {
            // reenable the inputs
            $inputs.prop("disabled", false);
        });

        // prevent default posting of form
        event.preventDefault();
    });

//    $("#regex-form").submit(function (e) {
//        e.preventDefault();
//
//        $("#submit").click();
//    })
});

var handleResponse = function (response) {
    var obj = JSON.parse(response);
    var status = obj.status;

    // load the new picture
    if(status === "SUCCESS") {
        console.log("We were successful. Loading the Picture.");



    } else {
        // throw an error message.
        alert("There was an error. " + obj.message);
    }
}