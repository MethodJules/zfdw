<?php
/**
 * Created by PhpStorm.
 * User: julien
 * Date: 19.10.18
 * Time: 10:13
 */

function create_one_time_link_page() {
    //add css
    drupal_add_css(drupal_get_path('module', 'create_one_time_link') . '/css/create_one_time_link.css');


    $table = create_one_time_link_create_table();
    $form_email_links = drupal_get_form('form_create_one_time_link_create_link');
    $form_email_body = drupal_get_form('form_create_one_time_link_create_email_body');

    return drupal_render($form_email_body) . drupal_render($form_email_links) . $table;

}


function create_one_time_link_create_table() {
    if(db_table_exists('create_one_time_link_emails')) {
        $result = db_select('create_one_time_link_emails', 'emails')
            ->fields('emails')
            ->execute()
            ->fetchAll();
    } else {
        drupal_set_message("The table 'create_one_time_link_emails' does not exist, please reinstall the module");

    }

    //dsm($result);


    $header = array('Salutatuion', 'Title', 'First Name', 'Surname' , 'Projekt', 'Email', 'Link', 'Email Sent', 'Action');

    $rows = array();
    foreach ($result as $result_row) {
        $row = array(
           'Salutation' => $result_row->salutation,
          'Title' => $result_row->title,
          'First Name' => $result_row->firstname,
          'Surname' => $result_row->surname,
          'Projekt' => $result_row->projekt,
          'Email' => $result_row->email,
          'Link' => $result_row->link,
          'Email Sent' => $result_row->email_sent,
          'Action' => ($result_row->email_sent === 'no') ? "<div id='cotl'><a class='send_email' href='./send_email/" . $result_row->link_email_id . "' >Send Email</a></div>" : "<div id='cotl'><a class='email_sent' href='#'>Email was sent</a></div>" ,

        );

        array_push($rows, $row);
    }

    $flag = "<a href='#'>" . t("Send Email") . "</a>";

    //$rows = array(array('hoferj@uni-hildesheim.de', 'Link1', $flag), array('hoferj@uni-hildesheim.de', 'Link1', $flag));

    $table = theme('table', array('header' => $header, 'rows' => $rows));

    return $table;

}