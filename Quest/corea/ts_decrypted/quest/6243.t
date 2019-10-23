CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 1;
	tid = 6243;
	title = 624302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActWorldPlayScript
			{
				sid = 6243;
				start = 0;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "4;";
			type = 1;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 624309;
				ctype = 1;
				idx = 3148101;
				taid = 2;
			}
			CDboTSActWorldPlayScript
			{
				sid = 6243;
				start = 1;
				taid = 3;
				uof = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 624308;
				gtype = 3;
				area = 624301;
				goal = 624304;
				grade = 132203;
				rwd = 100;
				sort = 624305;
				stype = 2;
				taid = 1;
				title = 624302;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSRcvSvrEvt
			{
				id = 341;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 624314;
			nextlnk = 4;
			rwdtbl = 624301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 0;

			CDboTSClickNPC
			{
				npcidx = 3148102;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 624307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3148101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "6242;";
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 624308;
			gtype = 3;
			oklnk = 2;
			area = 624301;
			goal = 624304;
			sort = 624305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 624302;
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 624307;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
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

			CDboTSActQItem
			{
				taid = 1;
				type = 1;
			}
		}
	}
}

