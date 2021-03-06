import pytest
import asyncio
import subprocess
from signal import Signals
import time
import os


@pytest.fixture(scope='module')
def connection(request):
    loop = asyncio.get_event_loop()
    reader, writer = loop.run_until_complete(asyncio.open_connection('127.0.0.1',
        15000, loop=loop))
    def fin():
        writer.close()  # Close the socket
        loop.close()
    request.addfinalizer(fin)
    return reader, writer, loop


@pytest.fixture(params=[32, 128, int(5e5)])
def bstr_size(request):
    return request.param


@pytest.fixture(scope='session')
def run_server(request):
    proc = subprocess.Popen(['./exoredis', 'ftest.erdb'])
    def fin():
        proc.send_signal(Signals.SIGINT)
        time.sleep(0.5)
        os.remove('ftest.erdb')
    request.addfinalizer(fin)
