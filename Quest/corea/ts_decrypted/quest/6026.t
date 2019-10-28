CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6026;
	title = 602602;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 7;
			elnk = 255;
			nextlnk = 253;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 6;
			elnk = 255;
			nextlnk = 100;
			prelnk = "5;";

			CDboTSActWorldPlayScript
			{
				sid = 6026;
				start = 0;
				taid = 2;
				uof = 0;
			}
			CDboTSActETimerE
			{
				taeid = 5;
				taid = 1;
				tceid = 2;
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 255;
			nextlnk = 6;
			prelnk = "3;";

			CDboTSActSendSvrEvt
			{
				id = 196;
				tblidx = 6026;
				stradius = 0;
				stype = 0;
				taid = 1;
				ttype = 255;
				type = 6;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 254;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActETimerS
			{
				sort = 0;
				taid = 5;
				tgid = 1;
				time = 600000;
			}
			CDboTSActNPCConv
			{
				conv = 602609;
				ctype = 1;
				idx = 4511108;
				taid = 1;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6026;
				start = 1;
				taid = 4;
				uof = 0;
			}
			CDboTSActRegQInfo
			{
				cont = 602608;
				gtype = 3;
				area = 602601;
				goal = 602604;
				m0fz = "-2597.000000";
				m0widx = 1;
				sort = 602605;
				stype = 8;
				m0fy = "-77.000000";
				grade = -1;
				m0fx = "5816.000000";
				m0ttip = 602615;
				rwd = 100;
				taid = 3;
				title = 602602;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 2;
				eitype = 0;
				idx0 = 5872100;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = 5873100;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 5;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602614;
			nextlnk = 7;
			rwdtbl = 602601;
			rwdtype = 0;
			ltime = -1;
			prelnk = "6;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4511108;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602608;
			gtype = 3;
			oklnk = 2;
			area = 602601;
			goal = 602604;
			sort = 602605;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602602;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "7;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 602607;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4511108;
			}
			CDboTSCheckPCCls
			{
				clsflg = 8;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6025;";
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;1;0;";
			type = 0;
		}
	}
	CNtlTSGroup
	{
		gid = 1;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
		CDboTSContGAct
		{
			cid = 1;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActTSState
			{
				state = 2;
				taid = 1;
				type = 0;
			}
		}
	}
}

