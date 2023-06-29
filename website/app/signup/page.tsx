'use client'
import React from 'react';
import Image from 'next/image';
import TakiLogo from "../taki_logo.png";
import { useRouter } from 'next/navigation';
import { sendMsg, getJsonResponse } from '../websocket';
import { useGlobalState } from '../globals';

const signupCode = process.env.SIGNUP_CODE;
const succesCode = process.env.SUCCESS;


const SignUpForum = () => {
  const [email, setEmail] = React.useState('');
  const [user_name, setName] = React.useState('');
  const [user_password, setPassword] = React.useState('');
  const [global_username, setUsername] = useGlobalState("username");
  const [global_password, setGPass] = useGlobalState("password");
  const router = useRouter();


  const handleSumbit = async (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    
    const message = `"email":"${email}","username":"${user_name}","password":"${user_password}"`;
    handleMsg(message, user_name, user_password, setUsername, setGPass).then((result) => { if (result) router.push('./');});
  };

    return (
        <nav className="flex items-center justify-center min-h-screen">
            <div className='text-center bg-white p-14 shadow-md rounded-md sm:max-w-lg mx-16'>
                <h2 className="text-3xl">Create an account</h2>
                <form onSubmit={handleSumbit}>
                    <input
                    type="email"
                    placeholder="Enter your email"
                    onChange={(e) => setEmail(e.target.value)}
                    className='rounded px-16 py-2 mt-8 border-2 border-gray-300'
                    required
                    />
                    <input
                    type="text"
                    placeholder="Enter your username"
                    onChange={(e) => setName(e.target.value)}
                    className='rounded px-16 py-2 mt-8 border-2 border-gray-300'
                    required
                    />
                    <br/>
                    <input 
                    type="password" 
                    placeholder="Enter your password" 
                    onChange={(e) => setPassword(e.target.value)}
                    className='rounded px-16 py-2 my-7 border-2 border-gray-300'
                    required
                    />
                    <br/>
                    <button
                    type="submit"
                    className="bg-blue-500 text-white py-2 px-32 rounded-md text-center hover:bg-gradient-to-r from-blue-500 to-blue-400"
                    >
                    Submit
                    </button>
                </form>
                <p className='mt-3'>Already have an account? <a className='text-blue-900 underline' href='/login'>Log in</a></p>
            </div>
        </nav>


    );
}

function handleMsg(msg : string, user_name : string, password : string, setUsername : Function, setGPass : Function) : Promise<boolean>
{
  
  return sendMsg(signupCode!.charAt(0), msg).then((response) => 
  {
    if (getJsonResponse(response).status == succesCode) 
    {
      setUsername(user_name);
      localStorage.setItem('username', user_name);

      setGPass(password);
      localStorage.setItem('password', password);

      return true;
    } 
    else 
    {
      alert(`User ${user_name} already exists`);
      return false;
    }
  })
  .catch((error) => 
  {
    alert(error);
    return false;
  });
}

const HomeBarLink = () => 
{
    return (
      <div>
        <a href="./">
          <Image src={TakiLogo} alt="My Image" width={100} height={100} className='cursor-pointer'/>
        </a>
      </div>
    )
}
  
const MyNavBar = () => 
{
    return (
      <div className=' bg-white sticky shadow-md border-blue-500'>
        <div className='flex justify-center items-center h-16'>
          <HomeBarLink />
        </div>
      </div>
    )
}
  
export default function signUp() 
{
    return (
      <main className=" bg-slate-200 w-screen h-screen">
        <div className=" w-screen h-16 fixed">
        <MyNavBar/>
        </div>
        <div>
          <SignUpForum/>
        </div>
      </main>
    )
}