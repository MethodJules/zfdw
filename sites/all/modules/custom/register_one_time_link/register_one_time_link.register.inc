<?php
/**
 * Created by PhpStorm.
 * User: julien
 * Date: 20.10.18
 * Time: 09:05
 */


function register_one_time_link_register($uid, $timestamp, $expire_timestamp, $hashed_pass, $redirect) {
    global $user;


    dsm($uid);

    //get data from database
    $result = db_select('create_one_time_link', 'cotl')
        ->fields('cotl')
        ->execute()
        ->fetchAssoc();
    //dsm($result);

    //check if user already logged in
    if($user->uid) {
        drupal_set_message(t('It is not necessary to use this link to login anymore. You are already logged in.'));
        drupal_goto('node/add/projekt');
    } else {
        // dsm($result);
        $account = user_load($uid);
        //drupal_session_regenerate();
        dsm($account);
        //check if uid and hash are the same
        if($account->status == 1) {
            //redirect to add project page
            $user = $account;
            user_login_finalize();
            drupal_goto('node/add/projekt');
        } else {
            drupal_set_message('Falsch');
            drupal_set_message('UID: ' . $result['uid'] . ' hash: ' . $result->hashed_pass);
            drupal_goto('<front>');
        }
    }


}