CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1243;
	title = 124302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 102;
			prelnk = "100;";

			CDboTSActSendSvrEvt
			{
				id = 168;
				tblidx = 1243;
				stradius = 0;
				stype = 0;
				taid = 1;
				ttype = 255;
				type = 6;
			}
		}
		CDboTSContGAct
		{
			cid = 103;
			elnk = 255;
			nextlnk = 254;
			prelnk = "102;";

			CDboTSActWorldPlayScript
			{
				sid = 1243;
				start = 0;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGCond
		{
			cid = 102;
			prelnk = "101;";
			nolnk = 255;
			rm = 1;
			yeslnk = 103;

			CDboTSRcvSvrEvt
			{
				id = 172;
			}
		}
		CDboTSContGAct
		{
			cid = 4;
			elnk = 3;
			nextlnk = 100;
			prelnk = "3;";

			CDboTSActWorldPlayScript
			{
				sid = 1243;
				start = 1;
				taid = 1;
				uof = 0;
			}
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "4;2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 4;

			CDboTSClickNPC
			{
				npcidx = 5042101;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 124309;
				ctype = 1;
				idx = 4111101;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 124308;
				gtype = 1;
				area = 124301;
				goal = 124304;
				grade = 132203;
				rwd = 100;
				sort = 124305;
				stype = 2;
				taid = 1;
				title = 124302;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 124307;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 4111101;
			}
			CDboTSCheckLvl
			{
				maxlvl = 51;
				minlvl = 43;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "103;";
			type = 1;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 124308;
			gtype = 1;
			oklnk = 2;
			area = 124301;
			goal = 124304;
			sort = 124305;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 124302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 124314;
			nextlnk = 101;
			rwdtbl = 124301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "4;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5042101;
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

