// Copyright (c) 2018, Ombre Cryptocurrency Project
// Copyright (c) 2018, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// Ombre changes to this code are in public domain. Please note, other licences may apply to the file.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once

#include <boost/thread/thread.hpp>
#include <memory>
#include <string>
#include <zmq.hpp>

#include "common/command_line.h"

#include "rpc_handler.h"

namespace cryptonote
{

namespace rpc
{

static constexpr int DEFAULT_NUM_ZMQ_THREADS = 1;
static constexpr int DEFAULT_RPC_RECV_TIMEOUT_MS = 1000;

class ZmqServer
{
  public:
	ZmqServer(RpcHandler &h);

	~ZmqServer();

	static void init_options(boost::program_options::options_description &desc);

	void serve();

	bool addIPCSocket(std::string address, std::string port);
	bool addTCPSocket(std::string address, std::string port);

	void run();
	void stop();

  private:
	RpcHandler &handler;

	volatile bool stop_signal;
	volatile bool running;

	zmq::context_t context;

	boost::thread run_thread;

	std::unique_ptr<zmq::socket_t> rep_socket;
};

} // namespace cryptonote

} // namespace rpc
