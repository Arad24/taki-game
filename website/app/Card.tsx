'use client'
import React from 'react';
import Image from 'next/image';
import { sendMsg, getJsonResponse } from './websocket';
import { useRouter } from 'next/navigation';
import { useGlobalState } from './globals';

const getRoomsCode = process.env.GETROOMS_CODE;
const succesCode = process.env.SUCCESS;

type Types = {
    content: string;
    title: string;
    image: string;
    btnLink: string;
};

const Card: React.FC<Types> = ({ title, content, image, btnLink }) => 
{
    const router = useRouter();
    const [global_username, setUsername] = useGlobalState("username");

    return (
        <div className='bg-white text-white shadow-md my-5 mx-6 rounded-md h-52 md:mx-20 lg:w-1/2 lg:mx-4 lg:h-96 flex items-center px-10'>
            <div className='flex-none mr-5'>
                <Image src={image} alt="Card Image" className="object-contain h-36 w-36 rounded-md lg:h-48 lg:w-48" width={100} height={100} />
            </div> 
            <div className='flex-grow text-black text-center '>
                <h1 className='border-b-2 inline-block text-lg lg:text-2xl'>{title}</h1>
                <p className='pt-5 min-h-12 lg:text-lg md:mb-3 lg:mb-10 mb-2 '>{content}</p>
                <button onClick={() => { if(global_username == '') btnLink = '/login'; router.push(btnLink)}} className='w-44 border-blue-500 border-2 rounded-md px-2 text-blue-500 text-sm hover:bg-blue-500 hover:text-white lg:text-md lg:w-1/2 xl:text-lg' >{title}</button>
            </div>  
        </div>
        
    );
};

export default Card;