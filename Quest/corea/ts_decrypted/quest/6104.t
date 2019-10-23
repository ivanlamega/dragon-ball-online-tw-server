CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 1;
	tid = 6104;
	title = 610402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				eitype = 4;
				idx0 = -1;
				rate0 = "1.000000";
				cnt0 = 0;
				ectype = -1;
				etype = 1;
				nidx0 = -1;
				taid = 1;
				esctype = 0;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "2;1;0;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 610408;
			gtype = 1;
			oklnk = 2;
			area = 610401;
			goal = 610404;
			sort = 610405;
			prelnk = "0;";
			ds = 0;
			grade = 157103;
			rwd = 100;
			title = 610402;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 610407;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2413104;
			}
			CDboTSCheckLvl
			{
				maxlvl = 50;
				minlvl = 41;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			didx0 = 19004;
			dval0 = 1;
			desc = 610414;
			nextlnk = 101;
			rwdtbl = 0;
			rwdtype = 0;
			dtype0 = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 0;

			CDboTSClickNPC
			{
				npcidx = 2413104;
			}
			CDboTSCheckSToCEvt
			{
				itype = 4;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 253;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 610409;
				ctype = 1;
				idx = 2413104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 610408;
				gtype = 1;
				area = 610401;
				goal = 610404;
				grade = 157103;
				rwd = 100;
				sort = 610405;
				stype = 1;
				taid = 1;
				title = 610402;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cd0 = 92019;
				eitype = 4;
				idx0 = 380;
				rate0 = "1.000000";
				cnt0 = 30;
				ectype = 0;
				etype = 0;
				nidx0 = -1;
				taid = 3;
				esctype = 0;
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 0;
			nolnk = 255;
			rm = 0;
			yeslnk = 2;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "0;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 380;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;";
			type = 0;
		}
	}
}

