CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6032;
	title = 603202;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 603207;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckPCCls
			{
				clsflg = 16;
			}
			CDboTSClickNPC
			{
				npcidx = 4752105;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6031;";
			}
		}
		CDboTSContGAct
		{
			cid = 5;
			elnk = 254;
			nextlnk = 6;
			prelnk = "3;";

			CDboTSActETimerS
			{
				sort = 1;
				taid = 2;
				tgid = 11;
				time = 3000;
			}
			CDboTSActEscort
			{
				start = 1;
				tblidx = 4752105;
				tsshare = 1;
				etype = 0;
				taid = 1;
			}
			CDboTSActETimerS
			{
				sort = 1;
				taid = 3;
				tgid = 12;
				time = 3000;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "5;0;1;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 3;
			elnk = 255;
			nextlnk = 5;
			prelnk = "2;";

			CDboTSActTWaitTS
			{
				taid = 1;
				time = 3000;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 603209;
				ctype = 1;
				idx = 4752105;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 603208;
				gtype = 3;
				area = 603201;
				goal = 603204;
				grade = -1;
				rwd = 100;
				sort = 603205;
				stype = 0;
				taid = 1;
				title = 603202;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 603214;
			nextlnk = 253;
			rwdtbl = 603201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "7;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4751104;
			}
		}
		CDboTSContGAct
		{
			cid = 7;
			elnk = 255;
			nextlnk = 100;
			prelnk = "6;";

			CDboTSActEscort
			{
				start = 0;
				tblidx = 4752105;
				tsshare = 1;
				etype = 0;
				taid = 1;
			}
			CDboTSActETimerE
			{
				taeid = 3;
				taid = 3;
				tceid = 5;
			}
			CDboTSActETimerE
			{
				taeid = 2;
				taid = 2;
				tceid = 5;
			}
		}
		CDboTSContGCond
		{
			cid = 6;
			prelnk = "5;";
			nolnk = 255;
			rm = 0;
			yeslnk = 7;

			CDboTSRcvSvrEvt
			{
				id = 603201;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 603208;
			gtype = 3;
			oklnk = 2;
			area = 603201;
			goal = 603204;
			sort = 603205;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 603202;
		}
	}
	CNtlTSGroup
	{
		gid = 12;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 603207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckNPCDead
			{
				idxlist = "4752105;";
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
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
	CNtlTSGroup
	{
		gid = 11;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 603207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;

			CDboTSCheckDistWithNPC
			{
				dist = "30.000000";
				idxlist = "4752105;";
			}
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

