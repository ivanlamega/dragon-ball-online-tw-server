CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6020;
	title = 602002;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 254;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 602009;
				ctype = 1;
				idx = 3181301;
				taid = 1;
			}
			CDboTSActETimerS
			{
				sort = 0;
				taid = 5;
				tgid = 1;
				time = 600000;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6020;
				start = 1;
				taid = 4;
				uof = 0;
			}
			CDboTSActRegQInfo
			{
				cont = 602008;
				gtype = 3;
				area = 602001;
				goal = 602004;
				m0fz = "-2319.270020";
				m0widx = 1;
				sort = 602005;
				stype = 8;
				m0fy = "-40.127998";
				grade = -1;
				m0fx = "4437.520020";
				m0ttip = 602015;
				rwd = 100;
				taid = 3;
				title = 602002;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 9811100;
				cnt0 = 10;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActWorldPlayScript
			{
				sid = 6020;
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
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 602014;
			nextlnk = 5;
			rwdtbl = 602001;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 3181301;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 602007;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 2;
			}
			CDboTSClickNPC
			{
				npcidx = 3181301;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6019;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "5;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;0;1;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 602008;
			gtype = 3;
			oklnk = 2;
			area = 602001;
			goal = 602004;
			sort = 602005;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 602002;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 1;

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
	}
}

